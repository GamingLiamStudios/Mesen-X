#pragma once
#include "Console.h"
#include "IMemoryHandler.h"
#include "stdafx.h"

class Mapper559MemoryHandler : public IMemoryHandler
{
    Console* _console;
    uint8_t _mask;

  public:
    Mapper559MemoryHandler(Console* console)
    {
        _console = console;
        _mask = 0;
    }

    uint8_t GetMask() { return _mask; }

    void GetMemoryRanges(MemoryRanges& ranges) override {}
    uint8_t ReadRAM(uint16_t addr) override { return 0; }

    void WriteRAM(uint16_t addr, uint8_t value) override
    {
        _console->GetPpu()->WriteRAM(addr, value);
        if ((addr & 0x07) == 0x01)
            _mask = value;
    }
};