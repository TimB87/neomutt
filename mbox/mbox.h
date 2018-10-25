/**
 * @file
 * Mbox local mailbox type
 *
 * @authors
 * Copyright (C) 1996-2002,2010,2013 Michael R. Elkins <me@mutt.org>
 * Copyright (C) 2018 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @page mbox MBOX: Local mailbox type
 *
 * Mbox local mailbox type
 *
 * | File        | Description        |
 * | :---------- | :----------------- |
 * | mbox/mbox.c | @subpage mbox_mbox |
 */

#ifndef MUTT_MBOX_MBOX_H
#define MUTT_MBOX_MBOX_H

#include <stdbool.h>

struct Mailbox;
struct stat;

/**
 * struct MboxAccountData - Private Account data
 */
struct MboxAccountData
{
  FILE *fp;              /**< Mailbox file */
  struct timespec atime; /**< File's last-access time */

  bool locked : 1; /**< is the mailbox locked? */
  bool append : 1; /**< mailbox is opened in append mode */
};

extern struct MxOps mx_mbox_ops;
extern struct MxOps mx_mmdf_ops;

#define MMDF_SEP "\001\001\001\001\n"

void mbox_reset_atime(struct Mailbox *m, struct stat *st);
int  mbox_path_probe(const char *path, const struct stat *st);
bool mbox_test_new_folder(const char *path);

#endif /* MUTT_MBOX_MBOX_H */