#pragma once
#include "Core/clsUser.h"

static clsUser CurrentUser = clsUser::Find("");
static bool IsSystemLocked = false;
static const short ENCRYPTION_KEY = 2;
