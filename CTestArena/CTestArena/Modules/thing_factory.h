//
//  thing_factory.h
//  CTestArena
//
//  Created by Brandon Stansbury on 4/1/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#ifndef CTestArena_thing_factory_h
#define CTestArena_thing_factory_h

struct thing {
    char name[20];
    int value;
};

struct thing create_thing(void);

#endif
