# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(Q3)
target_sources(app PRIVATE
  src/main.c
  src/launch_system.c
  src/missile.c
  src/timeout_monitor.c
  src/communication.c
  src/timers.c
)

