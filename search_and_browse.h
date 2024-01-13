// search_and_browse.h

#ifndef SEARCH_AND_BROWSE_H
#define SEARCH_AND_BROWSE_H

#include "book_circulation.h"  


void searchByAuthor(const char authorName[], struct BookNode* catalogHead);
void searchByTitle(const char titleName[], struct BookNode* catalogHead);
void searchAndBrowse();

#endif
