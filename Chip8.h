#pragma once
#ifndef CHIP8_H_INCLUDED
#define CHIP8_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

typedef unsigned char BYTE;
typedef unsigned short int WORD;

const int ROMSIZE = 0xFFF;

class Chip8
{

public:
	~Chip8();
	static	Chip8* CreateSingleton();
	bool	LoadRom(const std::string& romName);
	void	ExecuteNextOpcode();
	void	DecreaseTimers();
	void	KeyPressed(int key);
	void	KeyReleased(int key);

	BYTE	m_ScreenData[320][640][3];
private:
	Chip8();
	WORD	getNextOpcode();
	void	PlayBeep();
	int		getKeyPressed();

	void	CPUReset();
	void	ClearScreen();

	void	decodeOpcode0(WORD opcode);
	void	decodeOpcode8(WORD opcode);
	void	DecodeOpcodeE(WORD opcode);
	void	DecodeOpcodeF(WORD opcode);

	void	Opcode00EE();
	void	Opcode1NNN(WORD opcode);
	void	Opcode2NNN(WORD opcode);
	void	Opcode3XNN(WORD opcode);
	void	Opcode4XNN(WORD opcode);
	void	Opcode5XY0(WORD opcode);
	void	Opcode6XNN(WORD opcode);
	void	Opcode7XNN(WORD opcode);
	void	Opcode8XY0(WORD opcode);
	void	Opcode8XY1(WORD opcode);
	void	Opcode8XY2(WORD opcode);
	void	Opcode8XY3(WORD opcode);
	void	Opcode8XY4(WORD opcode);
	void	Opcode8XY5(WORD opcode);
	void	Opcode8XY6(WORD opcode);
	void	Opcode8XY7(WORD opcode);
	void	Opcode8XYE(WORD opcode);
	void	Opcode9XY0(WORD opcode);
	void	OpcodeANNN(WORD opcode);
	void	OpcodeBNNN(WORD opcode);
	void	OpcodeCXNN(WORD opcode);
	void	OpcodeDXYN(WORD opcode);
	void	OpcodeEX9E(WORD opcode);
	void	OpcodeEXA1(WORD opcode);
	void	OpcodeFX07(WORD opcode);
	void	OpcodeFX0A(WORD opcode);
	void	OpcodeFX15(WORD opcode);
	void	OpcodeFX18(WORD opcode);
	void	OpcodeFX1E(WORD opcode);
	void	OpcodeFX29(WORD opcode);
	void	OpcodeFX33(WORD opcode);
	void	OpcodeFX55(WORD opcode);
	void	OpcodeFX65(WORD opcode);

	static	Chip8* m_Instance;

	BYTE m_GameMemory[ROMSIZE]; // 0xFFF bytes of memory
	BYTE m_Registers[16]; // 16 registers, 1 byte each
	WORD m_AddressI; // the 16-bit address register I
	WORD m_ProgramCounter; // the 16-bit program counter

	std::vector<BYTE> m_Stack; //the 16-bit stack
	BYTE m_KeyState[16];
	BYTE m_DelayTimer;
	BYTE m_SoundTimer;
};

#endif // CHIP8CPU_H_INCLUDED
