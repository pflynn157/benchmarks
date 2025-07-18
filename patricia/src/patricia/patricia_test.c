/*
 * patricia_test.c
 *
 * Patricia trie test code.
 *
 * This code is an example of how to use the Patricia trie library for
 * doing longest-prefix matching.  We begin by adding a default
 * route/default node as the head of the Patricia trie.  This will become
 * an initialization functin (pat_init) in the future.  We then read in a
 * set of IPv4 addresses and network masks from "pat_test.txt" and insert
 * them into the Patricia trie.  I haven't _yet_ added example of searching
 * and removing nodes.
 *
 * Compiling the library:
 *     gcc -g -Wall -c patricia.c
 *     ar -r libpatricia.a patricia.o
 *     ranlib libpatricia.a
 *
 * Compiling the test code (or any other file using libpatricia):
 *     gcc -g -Wall -I. -L. -o ptest patricia_test.c -lpatricia
 *
 * Matthew Smart <mcsmart@eecs.umich.edu>
 *
 * Copyright (c) 2000
 * The Regents of the University of Michigan
 * All rights reserved
 *
 * $Id: patricia_test.c,v 1.1.1.1 2000/11/06 19:53:17 mguthaus Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "patricia.h"
#include "input.h"

struct in_addr
{
    uint32_t s_addr; // load with inet_aton()
};


int32_t inet_aton(const char *cp, struct in_addr *addr)
{
    register uint32_t val;
    register int32_t base, n;
    register char c;
    uint32_t parts[4];
    register uint32_t *pp = parts;

    c = *cp;
    for (;;)
    {
        /*
         * Collect number up to ``.''.
         * Values are specified as for C:
         * 0x=hex, 0=octal, isdigit=decimal.
         */
        if (!isdigit(c))
            return (0);
        val = 0;
        base = 10;
        if (c == '0')
        {
            c = *++cp;
            if (c == 'x' || c == 'X')
                base = 16, c = *++cp;
            else
                base = 8;
        }
        for (;;)
        {
            if (isascii(c) && isdigit(c))
            {
                val = (val * base) + (c - '0');
                c = *++cp;
            }
            else if (base == 16 && isascii(c) && isxdigit(c))
            {
                val = (val << 4) |
                      (c + 10 - (islower(c) ? 'a' : 'A'));
                c = *++cp;
            }
            else
                break;
        }
        if (c == '.')
        {
            /*
             * Internet format:
             *	a.b.c.d
             *	a.b.c	(with c treated as 16 bits)
             *	a.b	(with b treated as 24 bits)
             */
            if (pp >= parts + 3)
                return (0);
            *pp++ = val;
            c = *++cp;
        }
        else
            break;
    }
    /*
     * Check for trailing characters.
     */
    if (c != '\0' && (!isascii(c) || !isspace(c)))
        return (0);
    /*
     * Concoct the address according to
     * the number of parts specified.
     */
    n = pp - parts + 1;
    switch (n)
    {

    case 0:
        return (0); /* initial nondigit */

    case 1: /* a -- 32 bits */
        break;

    case 2: /* a.b -- 8.24 bits */
        if ((val > 0xffffff) || (parts[0] > 0xff))
            return (0);
        val |= parts[0] << 24;
        break;

    case 3: /* a.b.c -- 8.8.16 bits */
        if ((val > 0xffff) || (parts[0] > 0xff) || (parts[1] > 0xff))
            return (0);
        val |= (parts[0] << 24) | (parts[1] << 16);
        break;

    case 4: /* a.b.c.d -- 8.8.8.8 bits */
        if ((val > 0xff) || (parts[0] > 0xff) || (parts[1] > 0xff) || (parts[2] > 0xff))
            return (0);
        val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
        break;
    }
    if (addr)
    {
        addr->s_addr = val;
    }

    return (1);
}

int32_t main()
{
    struct ptree *phead;
    struct ptree *p, *pfind;
    struct in_addr addr;
    uint32_t mask = 0xffffffff;

    /*
     * Initialize the Patricia trie by doing the following:
     *   1. Assign the head pointer a default route/default node
     *   2. Give it an address of 0.0.0.0 and a mask of 0x00000000
     *      (matches everything)
     *   3. Set the bit position (p_b) to 0.
     *   4. Set the number of masks to 1 (the default one).
     *   5. Point the head's 'left' and 'right' pointers to itself.
     * NOTE: This should go into an intialization function.
     */
    phead = (struct ptree *)alloca(sizeof(struct ptree));
    bzero(phead, sizeof(*phead));
    bzero(phead->p_m, sizeof(struct ptree_mask));

    /*******
     *
     * Fill in default route/default node data here.
     *
     *******/
    phead->p_mlen = 1;
    phead->p_left = phead->p_right = phead;

    /*
     * The main loop to insert nodes.
     */
    fakeFile = input_data;
    while (fakeFile < (input_data + sizeof(input_data) / sizeof(struct input_data_format)))
    {
        /*
         * Read in each IP address and mask and convert them to
         * more usable formats.
         */
        inet_aton(fakeFile->addr, &addr);
        ++fakeFile;

        /*
         * Create a Patricia trie node to insert.
         */
        p = (struct ptree *)alloca(sizeof(struct ptree));
        bzero(p, sizeof(*p));

        /*
         * Allocate the mask data.
         */
        bzero(p->p_m, sizeof(struct ptree_mask));

        /*
         * Assign a value to the IP address and mask field for this node.
         */
        p->p_key = addr.s_addr;         /* Network-byte order */
        p->p_m->pm_mask = mask;

        pfind = pat_search(addr.s_addr, phead);
        if (pfind->p_key == addr.s_addr)
        {
            printf("%08x: Found\r\n", addr.s_addr);
        }
        else
        {
            /*
             * Insert the node.
             * Returns the node it inserted on success, 0 on failure.
             */
            p = pat_insert(p, phead);
            printf("%08x: Inserted\r\n", addr.s_addr);
        }
        if (!p)
        {
            printf("Failed on pat_insert\r\n");
            return (0);
        }
    }

    return (1);
}
