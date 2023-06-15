# SPDX-FileCopyrightText: 2023 KOINSLOT, Inc.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS "../")
SET(TEST_COMPONENTS "kywy")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(COMPONENTS main kywy)
project(kywy-tests)
