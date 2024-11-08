/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _UUID_H_
#define _UUID_H_

#include "ext4_utils.h"

void generate_uuid(const char *namespace, const char *name, u8 result[16]);

void uuid_parse(const char *uuid_str, u8 result[16]);

void uuid_to_str(const u8 uuid[16], char uuid_str[37]);

#endif
