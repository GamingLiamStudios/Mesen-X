#pragma once
#include "BaseMapper.h"
#include "Mapper559MemoryHandler.h"

class Mapper559 : public BaseMapper
{
  private:
    uint8_t _prgMode : 2;
    uint8_t _chrMode : 2;
    bool _expansionMode : 1;

    uint8_t _chrUpperBits;
    uint8_t _prgBanks[4];
    uint8_t _chrBanks[8];

    std::unique_ptr<Mapper559MemoryHandler> _memoryHandler;

    uint8_t _nametableRead;
    uint16_t _lastNametableAddress;
    uint8_t _lastAttribute;

    void UpdatePrgBanks()
    {
        switch (_prgMode) {
            case 0:
                SetCpuMemoryMapping(0x8000,
                                    0xFFFF,
                                    _prgBanks[3] & 0b11111100,
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                break;
            case 1:
                SetCpuMemoryMapping(0x8000,
                                    0xBFFF,
                                    _prgBanks[1] & 0b11111110,
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                SetCpuMemoryMapping(0xC000,
                                    0xFFFF,
                                    _prgBanks[3] & 0b11111110,
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                break;
            case 2:
                SetCpuMemoryMapping(0x8000,
                                    0xBFFF,
                                    _prgBanks[1] & 0b11111110,
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                SetCpuMemoryMapping(0xC000,
                                    0xDFFF,
                                    _prgBanks[2],
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                SetCpuMemoryMapping(0xE000,
                                    0xFFFF,
                                    _prgBanks[3],
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                break;
            case 3:
                SetCpuMemoryMapping(0x8000,
                                    0x9FFF,
                                    _prgBanks[0],
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                SetCpuMemoryMapping(0xA000,
                                    0xBFFF,
                                    _prgBanks[1],
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                SetCpuMemoryMapping(0xC000,
                                    0xDFFF,
                                    _prgBanks[2],
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                SetCpuMemoryMapping(0xE000,
                                    0xFFFF,
                                    _prgBanks[3],
                                    PrgMemoryType::PrgRom,
                                    MemoryAccessType::Read);
                break;
        }
    }

    void UpdateChrBanks()
    {
        switch (_chrMode) {
            case 0:
                SetPpuMemoryMapping(0x0000,
                                    0x1FFF,
                                    ((_chrBanks[7] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[7] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[7] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                break;
            case 1:
                SetPpuMemoryMapping(0x0000,
                                    0x0FFF,
                                    ((_chrBanks[3] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[3] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[3] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x1000,
                                    0x1FFF,
                                    ((_chrBanks[7] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[7] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[7] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                break;
            case 2:
                SetPpuMemoryMapping(0x0000,
                                    0x07FF,
                                    ((_chrBanks[1] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[1] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[1] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x0800,
                                    0x0FFF,
                                    ((_chrBanks[3] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[3] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[3] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x1000,
                                    0x17FF,
                                    ((_chrBanks[5] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[5] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[5] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x1800,
                                    0x1FFF,
                                    ((_chrBanks[7] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[7] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[7] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                break;
            case 3:
                SetPpuMemoryMapping(0x0000,
                                    0x03FF,
                                    ((_chrBanks[0] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[0] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[0] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x0400,
                                    0x07FF,
                                    ((_chrBanks[1] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[1] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[1] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x0800,
                                    0x0BFF,
                                    ((_chrBanks[2] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[2] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[2] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x0C00,
                                    0x0FFF,
                                    ((_chrBanks[3] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[3] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[3] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x1000,
                                    0x13FF,
                                    ((_chrBanks[4] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[4] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[4] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x1400,
                                    0x17FF,
                                    ((_chrBanks[5] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[5] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[5] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x1800,
                                    0x1BFF,
                                    ((_chrBanks[6] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[6] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[6] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                SetPpuMemoryMapping(0x1C00,
                                    0x1FFF,
                                    ((_chrBanks[7] & 0b01111111) |
                                     ((uint32_t)_chrUpperBits << 8)) &
                                      (_chrBanks[7] & 0x80 ? 0x0007 : 0xFFFF),
                                    _chrBanks[7] & 0x80 ? ChrMemoryType::ChrRam
                                                        : ChrMemoryType::ChrRom,
                                    MemoryAccessType::Read);
                break;
        }
    }

    inline void SwitchPrgBank(uint16_t addr, uint8_t data)
    {
        _prgBanks[addr - 0x5101] = data;
        UpdatePrgBanks();
    }

    inline void SwitchChrBank(uint16_t addr, uint8_t data)
    {
        _chrBanks[addr - 0x5105] = data;
        UpdateChrBanks();
    }

  protected:
    virtual uint16_t RegisterStartAddress() override { return 0x5100; }
    virtual uint16_t RegisterEndAddress() override { return 0x510D; }

    virtual uint16_t GetPRGPageSize() override { return 0x2000; }
    virtual uint16_t GetCHRPageSize() override { return 0x400; }
    virtual uint16_t GetChrRamPageSize() override { return 0x400; }
    virtual uint32_t GetChrRamSize() override { return 0x2000; }

    // Expansion RAM
    virtual uint32_t GetWorkRamSize() override { return 0x400; }
    virtual uint32_t GetWorkRamPageSize() override { return 0x400; }
    virtual bool ForceWorkRamSize() override { return true; }

    // Even if it isn't battery-backed, Save RAM should still be available
    virtual uint32_t GetSaveRamSize() override { return 0x2000; }
    virtual uint32_t GetSaveRamPageSize() override { return 0x2000; }
    virtual bool ForceSaveRamSize() override { return true; }

    virtual void InitMapper() override
    {
        SetCpuMemoryMapping(0x5400, 0x57FF, 0, PrgMemoryType::WorkRam);
        SetCpuMemoryMapping(0x6000, 0x7FFF, 0, PrgMemoryType::SaveRam);

        _memoryHandler.reset(new Mapper559MemoryHandler(_console.get()));

        _nametableRead = 0;

        // Default values
        WriteRegister(0x5100, 0x00);
        WriteRegister(0x5104, 0xFF);

        UpdateChrBanks();
    }

    void Reset(bool softReset) override
    {
        _console->GetMemoryManager()->RegisterWriteHandler(
          _memoryHandler.get(), 0x2000, 0x2007);
    }

    void WriteRegister(uint16_t addr, uint8_t value) override
    {
        if (addr >= 0x5101 && addr <= 0x5104)
            SwitchPrgBank(addr, value);
        else if (addr >= 0x5105 && addr <= 0x510C)
            SwitchChrBank(addr, value);
        else if (addr == 0x5100) {
            _prgMode = value & 0b11;
            _chrMode = (value >> 2) & 0b11;
            _expansionMode = (value >> 4) & 0b1;

            // This could probably be done better
            UpdatePrgBanks();
            UpdateChrBanks();
        } else if (addr == 0x510D)
            _chrUpperBits = value & 0b1111;
    }

    virtual uint8_t MapperReadVRAM(
      uint16_t addr,
      MemoryOperationType memoryOperationType) override
    {
        bool write = _memoryHandler->GetMask() & 0b00011000;

        if (addr >= 0x2000 && addr <= 0x2FFF && (addr & 0x03FF) < 0x03C0) {
            _nametableRead = 3;
            _lastNametableAddress = addr & 0x03FF;
        } else if (_nametableRead > 0) {
            _nametableRead--;
            switch (_nametableRead) {
                case 2: {
                    if ((addr & 0x03FF) < 0x03C0) {
                        _nametableRead = 0;
                        return InternalReadVRAM(addr);
                    }

                    // Attribute table read
                    _lastAttribute =
                      InternalReadRam(0x5400 + _lastNametableAddress);
                    if (!write)
                        return InternalReadVRAM(addr);

                    uint8_t attribute = (_lastAttribute & 0xC0) >> 6;
                    return attribute | attribute << 2 | attribute << 4 |
                           attribute << 6;
                }
                case 1:
                    if (addr < 0x1000) {
                        _nametableRead = 0;
                        return InternalReadVRAM(addr);
                    }
                case 0:
                    if (!write)
                        return InternalReadVRAM(addr);
                    /*
                        if (_lastAttribute & 0b00100000)
                            return _chrRam[(((uint16_t)_lastAttribute & 0x07)
                                            << 12) |
                                           (addr & 0x0FFF)];
                        else {
                            uint32_t chrAddr =
                              (((uint32_t)_chrUpperBits << 17) |
                               (((uint32_t)_lastAttribute & 0x1F) << 12)) %
                              _chrRomSize;
                            return _chrRom[chrAddr | (addr & 0x0FFF)];
                        }
                    */
            }
        }

        return InternalReadVRAM(addr);
    }
};