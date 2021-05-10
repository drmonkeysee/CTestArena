//
//  sortedlist.h
//  CTestArena
//
//  Created by Brandon Stansbury on 5/9/21.
//  Copyright © 2021 Brandon Stansbury. All rights reserved.
//

#ifndef CTestArena_sortedlist_h
#define CTestArena_sortedlist_h

typedef struct node slist;
typedef struct sortedvector svec;

slist *slist_new(void);
_Bool slist_search(slist *self, unsigned short a);

svec *svec_new(void);
_Bool svec_search(svec *self, unsigned short a);

#endif
