/**
 * @file
 * Create/manipulate threading in emails
 *
 * @authors
 * Copyright (C) 2017 Richard Russon <rich@flatcap.org>
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

#ifndef MUTT_MUTT_THREAD_H
#define MUTT_MUTT_THREAD_H

#include <stdbool.h>
#include <stdint.h>

struct Email;
struct EmailList;
struct Mailbox;
struct MuttThread;
struct ThreadsContext;

/* These Config Variables are only used in mutt_thread.c */
extern bool C_CollapseFlagged;
extern bool C_CollapseUnread;
extern bool C_DuplicateThreads;
extern bool C_HideLimited;
extern bool C_HideMissing;
extern bool C_HideThreadSubject;
extern bool C_HideTopLimited;
extern bool C_HideTopMissing;
extern bool C_NarrowTree;
extern bool C_SortRe;
extern bool C_StrictThreads;
extern bool C_ThreadReceived;

/**
 * enum TreeChar - Tree characters for menus
 *
 * @sa linearize_tree(), print_enriched_string()
 */
enum TreeChar
{
  MUTT_TREE_LLCORNER = 1, ///< Lower left corner
  MUTT_TREE_ULCORNER,     ///< Upper left corner
  MUTT_TREE_LTEE,         ///< Left T-piece
  MUTT_TREE_HLINE,        ///< Horizontal line
  MUTT_TREE_VLINE,        ///< Vertical line
  MUTT_TREE_SPACE,        ///< Blank space
  MUTT_TREE_RARROW,       ///< Right arrow
  MUTT_TREE_STAR,         ///< Star character (for threads)
  MUTT_TREE_HIDDEN,       ///< Ampersand character (for threads)
  MUTT_TREE_EQUALS,       ///< Equals (for threads)
  MUTT_TREE_TTEE,         ///< Top T-piece
  MUTT_TREE_BTEE,         ///< Bottom T-piece
  MUTT_TREE_MISSING,      ///< Question mark
  MUTT_TREE_MAX,

  MUTT_SPECIAL_INDEX = MUTT_TREE_MAX, ///< Colour indicator
};

typedef uint8_t MuttThreadFlags;         ///< Flags, e.g. #MUTT_THREAD_COLLAPSE
#define MUTT_THREAD_NO_FLAGS          0  ///< No flags are set
#define MUTT_THREAD_COLLAPSE    (1 << 0) ///< Collapse an email thread
#define MUTT_THREAD_UNCOLLAPSE  (1 << 1) ///< Uncollapse an email thread
#define MUTT_THREAD_GET_HIDDEN  (1 << 2) ///< Count non-visible emails in a thread
#define MUTT_THREAD_UNREAD      (1 << 3) ///< Count unread emails in a thread
#define MUTT_THREAD_NEXT_UNREAD (1 << 4) ///< Find the next unread email
#define MUTT_THREAD_FLAGGED     (1 << 5) ///< Count flagged emails in a thread

int mutt_traverse_thread(bool lmt, struct Email *e, MuttThreadFlags flag);
#define mutt_collapse_thread(lmt, e)         mutt_traverse_thread(lmt, e, MUTT_THREAD_COLLAPSE)
#define mutt_uncollapse_thread(lmt, e)       mutt_traverse_thread(lmt, e, MUTT_THREAD_UNCOLLAPSE)
#define mutt_get_hidden(lmt, e)              mutt_traverse_thread(lmt, e, MUTT_THREAD_GET_HIDDEN)
#define mutt_thread_contains_unread(lmt, e)  mutt_traverse_thread(lmt, e, MUTT_THREAD_UNREAD)
#define mutt_thread_contains_flagged(lmt, e) mutt_traverse_thread(lmt, e, MUTT_THREAD_FLAGGED)
#define mutt_thread_next_unread(lmt, e)      mutt_traverse_thread(lmt, e, MUTT_THREAD_NEXT_UNREAD)

int mutt_aside_thread(struct Email *e, bool forwards, bool subthreads);
#define mutt_next_thread(e)        mutt_aside_thread(e, true,  false)
#define mutt_previous_thread(e)    mutt_aside_thread(e, false, false)
#define mutt_next_subthread(e)     mutt_aside_thread(e, true,  true)
#define mutt_previous_subthread(e) mutt_aside_thread(e, false, true)

struct ThreadsContext *mutt_thread_ctx_init          (struct Mailbox *m);
void                   mutt_thread_ctx_free          (struct ThreadsContext **tctx);
void                   mutt_thread_collapse_collapsed(struct ThreadsContext *tctx, bool lmt);
void                   mutt_thread_collapse          (struct ThreadsContext *tctx, bool lmt, bool collapse);
bool                   mutt_thread_can_collapse      (bool lmt, struct Email *e);

void                   mutt_clear_threads     (struct ThreadsContext *tctx);
void                   mutt_draw_tree         (bool lmt, struct ThreadsContext *tctx);
bool                   mutt_link_threads      (struct Email *parent, struct EmailList *children, struct Mailbox *m);
struct HashTable *     mutt_make_id_hash      (struct Mailbox *m);
int                    mutt_messages_in_thread(struct Mailbox *m, struct Email *e, int flag);
int                    mutt_parent_message    (bool lmt, struct Email *e, bool find_root);
off_t                  mutt_set_vnum          (struct Mailbox *m, bool lmt, int padding);
void                   mutt_sort_subthreads   (struct ThreadsContext *tctx, bool init);
void                   mutt_sort_threads      (struct ThreadsContext *tctx, bool lmt, bool init);


#endif /* MUTT_MUTT_THREAD_H */
