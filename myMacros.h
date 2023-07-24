#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK_RETURN_0(p) if(!p) return 0;
#define CHECK_MSG_RETURN_0(p,msg) if(!p){printf(#msg "\n");return 0;}
#define FREE_CLOSE_FILE_RETURN_0(fp,p) {free(p); fclose(fp); return 0;}
#define CLOSE_RETURN_0(fp) {fclose(fp);return 0;}