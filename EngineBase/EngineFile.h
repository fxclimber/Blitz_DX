#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>

#include "EnginePath.h"

// ���ϰ� ���õ� ��� ����� ���⿡�� ����մϴ�.
// FIle ����
// �ڵ� ���ʿ� �߸�����ϱ⵵ ����� ¥�°��� ����Ʈ �Դϴ�.
// ����
// �̵�


const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
	// �ϵ��ڵ� 
public:
	ENGINEAPI UEngineFile();
	// ����ü��
	ENGINEAPI UEngineFile(const std::string& _Path);
	ENGINEAPI UEngineFile(std::string_view _Path);
	ENGINEAPI UEngineFile(std::filesystem::path _Path);
	ENGINEAPI UEngineFile(const UEnginePath& _Path);
	ENGINEAPI ~UEngineFile();

	// Write
	void Write(class UEngineSerializer& _Ser);
	void Read(class UEngineSerializer& _Ser);

	void Write(const void* _Ptr, size_t _Size);
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	void Close();

	int GetFileSize();

	// ��� Ŭ���� ����
private:
	// ���
	// _MAX_DIR �����쿡 �������� ���α׷�
	FILE* File = nullptr;
};
