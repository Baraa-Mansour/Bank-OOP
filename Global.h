#pragma once
#include "clsUser.h"

static clsUser CurrentUser = clsUser::Find("");
static bool IsSystemLocked = false;
