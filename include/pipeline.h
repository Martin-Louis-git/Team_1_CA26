#pragma once

#include "instruction_packet.h"

InstructionPacket fetch_decode;
InstructionPacket decode_execute;
InstructionPacket execute_memory;
InstructionPacket memory_write_back;