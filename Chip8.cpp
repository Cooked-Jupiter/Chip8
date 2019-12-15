#include "Chip8.h"
#include <assert.h>


/* NNN: Address. Can be accessed by opcode & 0x0FFF
 *  NN: 8-bit constant. Can be accessed by opcode & 0x00FF 
 *  Vx: The Vx register identifier. Can be accessed by opcode & 0x0F00
 *  Vy: The Vy register identifier. Can be accessed by opcode & 0x00F0
 *
 *
 *
 *
 *
 */
Chip8* Chip8::m_Instance = 0;

Chip8::~Chip8()
{
	delete m_Instance;
}

Chip8* Chip8::CreateSingleton()
{
	if (0 == m_Instance)
		m_Instance = new Chip8();
	return m_Instance;
}

Chip8::Chip8()
{

}

WORD Chip8::getNextOpcode()
{
	WORD res = 0;
	res = m_GameMemory[m_ProgramCounter];
	res <<= 8; //This shifts the bits 8 left
	res |= m_GameMemory[m_ProgramCounter + 1];
	m_ProgramCounter += 2;
	return res;
}

void Chip8::PlayBeep()
{
	std::cout << '\a';
}

int Chip8::getKeyPressed()
{
	int res = -1;
	for(int i = 0;i<16;i++)
	{
		if (m_KeyState[i] > 0)
			return i;
	}
	return res;
}

void Chip8::CPUReset()
{
	m_AddressI = 0;
	m_ProgramCounter = 0x200;
	memset(m_Registers, 0, sizeof(m_Registers));
	memset(m_GameMemory, 0, sizeof(m_GameMemory));
	memset(m_KeyState, 0, sizeof(m_KeyState));
	m_DelayTimer = 0;
	m_SoundTimer = 0;
}

void Chip8::ClearScreen()
{
	for (int x = 0; x < 640;x++) 
	{
		for (int y = 0; y < 320;y++) 
		{
			m_ScreenData[y][x][0] = 255;
			m_ScreenData[y][x][1] = 255;
			m_ScreenData[y][x][2] = 255;
		}
	}
}



bool Chip8::LoadRom(const std::string& romName)
{
	CPUReset();
	ClearScreen();
	FILE* in;
	in = fopen(romName.c_str(), "rb");

	if (0 == in)
		return false;

	fread(&m_GameMemory[0x200], ROMSIZE, 1, in);
	fclose(in);
	return true;
}

void Chip8::ExecuteNextOpcode()
{
	WORD opcode = getNextOpcode();
	switch(opcode & 0xF000)
	{
	case 0x0000: decodeOpcode0(opcode);break;
	case 0x1000: Opcode1NNN(opcode);break;
	case 0x2000: Opcode2NNN(opcode);break;
	default: break;
	}
}

void Chip8::DecreaseTimers()
{
	if(m_DelayTimer > 0)
	--m_DelayTimer;
	if(m_SoundTimer > 0)
	--m_SoundTimer;
	if (m_SoundTimer > 0)
		PlayBeep();
}

void Chip8::KeyPressed(int key)
{
	m_KeyState[key] = 1;

}

void Chip8::KeyReleased(int key)
{
	m_KeyState[key] = 0;

}

void Chip8::decodeOpcode0(WORD opcode)
{
}

void Chip8::decodeOpcode8(WORD opcode)
{
}

void Chip8::DecodeOpcodeE(WORD opcode)
{
}

void Chip8::DecodeOpcodeF(WORD opcode)
{
}

void Chip8::Opcode00EE()
{
	m_ProgramCounter = m_Stack.back();
	m_Stack.pop_back();
}

void	Chip8::Opcode1NNN(WORD opcode)
{
	m_ProgramCounter = opcode & 0x0FFF; // remember we're only interested in NNN of opcode 1NNN
}

void Chip8::Opcode2NNN(WORD opcode)
{
	m_Stack.push_back(m_ProgramCounter); // save the program counter
	m_ProgramCounter = opcode & 0x0FFF; // jump to address NNN
}

void	Chip8::Opcode3XNN(WORD opcode)
{
	int NN = opcode & 0x00FF;
	int regx = opcode & 0x0F00;
	regx >>= 8;//This offsets it by 8 bits
	if (m_Registers[regx] == NN)
		m_ProgramCounter += 2;
}

void	Chip8::Opcode4XNN(WORD opcode)
{
	int NN = opcode & 0x00FF; //NN: 8-bit constant
	int regx = opcode & 0x0F00;
	regx >>= 8;
	if (m_Registers[regx] != NN)
		m_ProgramCounter += 2;
}
void	Chip8::Opcode5XY0(WORD opcode)
{
	int regx = opcode & 0x0F00;
	regx >>= 8;
	int regy = opcode & 0x00F0;
	regy >>= 4;
	if (m_Registers[regx] == m_Registers[regy])
		m_ProgramCounter += 2;

}
void	Chip8::Opcode6XNN(WORD opcode) 
{
	int NN = opcode & 0x00FF; //NN: 8-bit constant

	int regx = opcode & 0x0F00;
	regx >>= 8;
	m_Registers[regx] = NN;
}
void	Chip8::Opcode7XNN(WORD opcode) {}
void	Chip8::Opcode8XY0(WORD opcode) {}
void	Chip8::Opcode8XY1(WORD opcode) {}
void	Chip8::Opcode8XY2(WORD opcode) {}
void	Chip8::Opcode8XY3(WORD opcode) {}
void	Chip8::Opcode8XY4(WORD opcode) {}
void	Chip8::Opcode8XY5(WORD opcode) {}
void	Chip8::Opcode8XY6(WORD opcode) {}
void	Chip8::Opcode8XY7(WORD opcode) {}
void	Chip8::Opcode8XYE(WORD opcode) {}
void	Chip8::Opcode9XY0(WORD opcode) {}
void	Chip8::OpcodeANNN(WORD opcode) {}
void	Chip8::OpcodeBNNN(WORD opcode) {}
void	Chip8::OpcodeCXNN(WORD opcode) {}
void	Chip8::OpcodeDXYN(WORD opcode) {}
void	Chip8::OpcodeEX9E(WORD opcode) {}
void	Chip8::OpcodeEXA1(WORD opcode) {}
void	Chip8::OpcodeFX07(WORD opcode) {}
void	Chip8::OpcodeFX0A(WORD opcode) {}
void	Chip8::OpcodeFX15(WORD opcode) {}
void	Chip8::OpcodeFX18(WORD opcode) {}
void	Chip8::OpcodeFX1E(WORD opcode) {}

void	Chip8::OpcodeFX29(WORD opcode)
{
}
void	Chip8::OpcodeFX33(WORD opcode) {}
void	Chip8::OpcodeFX55(WORD opcode) {}
void	Chip8::OpcodeFX65(WORD opcode) {}