#include <rdecommon.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "..\math\local.h"
#include "settingfile.h"

namespace oglElements {

	ConfigRecord::ConfigRecord()
		: name("")
		, type(eConfigType::eString)
		, pVariable(0)
	{
	}

	ConfigRecord::ConfigRecord(std::string _name, eConfigType t, void* pVar)
		: name(_name)
		, type(t)
		, pVariable(pVar)
	{
	}

	ConfigRecord::ConfigRecord(std::string _name, eConfigType t, const void* pVar)
		: name(_name)
		, type(t)
		, pVariable(const_cast<void*>(pVar))
	{
	}

	void SettingFile::setSettings(const std::vector<ConfigRecord>& records)
	{
		varList = records;
	}

	bool SettingFile::load(const std::string& filePath)
	{
		FILE* fp = nullptr;
		const int bufferlen = 255;
		char line[bufferlen];
		fopen_s(&fp, filePath.c_str(), "r");
		bool success = false;
		if (fp != nullptr)
		{
			std::vector<StrKeyValue> fileConfigs;

			while (fgets(line, bufferlen, fp))
			{
				std::vector<std::string> lineTokens;
				std::string token;
				std::stringstream ss(line);
				while (std::getline(ss, token, ':'))
				{
					lineTokens.push_back(trim(token));
				}

				StrKeyValue rec;
				rec.name = lineTokens[0];
				rec.value = lineTokens[1];

				fileConfigs.push_back(rec);
			}

			fclose(fp);
			// implement loading values to varList

			for (auto config : fileConfigs)
			{
				setConfigValue(getConfig(config.name), config.value);
			}
			success = true;
		}
		else
		{
			tracelog(format("error reading file %s", filePath.c_str()));
		}

		
		return success;
	}

	bool SettingFile::save(const std::string& filePath)
	{
		std::fstream file;
	
		file.open(filePath.c_str(), std::fstream::out);

		if (!file.is_open())
		{
			tracelog(format("Unable to open the file %s .", filePath.c_str()));
			return 0;
		}

		for (auto var : varList)
		{
			std::string line;
			Vector3f* data;
			switch (var.type)
			{
			case eConfigType::eString:
				line = format("%s : %s \n", var.name.c_str(), ((std::string*)var.pVariable)->c_str());
				break;
			case eConfigType::eInt32:
				line = format("%s : %i \n", var.name.c_str(), *(int32*)var.pVariable);
				break;
			case eConfigType::eFloat32:
				line = format("%s : %f \n", var.name.c_str(), *(float32*)var.pVariable);
				break;
			case eConfigType::eVector3f:
				data = (Vector3f*)var.pVariable;
				line = format("%s : %f,%f,%f \n", var.name.c_str(), (*data)[0], (*data)[1], (*data)[2]);
				break;
			}
			file << line;
		}

		file.close();
		return true;

	}

	ConfigRecord* SettingFile::getConfig(const std::string& key)
	{
		for (int i=0;i<varList.size();i++)
		{
			if (varList[i].name == key)
				return &varList[i];
		}
		return 0;
	}

	void SettingFile::setConfigValue(ConfigRecord* var, const std::string& value)
	{
		if (var == 0) return;

		switch (var->type)
		{
		case eString:
			*(std::string*)var->pVariable = value;
			break;
		case eConfigType::eInt32:
			*(int32*)var->pVariable = std::stoi(value);
			break;
		case eConfigType::eFloat32:
			*(float32*)var->pVariable = std::stof(value);
			break;
		case eConfigType::eVector3f:
			int32 i = 0;
			Vector3f v;
			std::stringstream ss(value);
			std::string token;
			while (std::getline(ss, token, ','))
			{
				v[i++] = stof(token);
			}
			func::vCopy(*((Vector3f*)var->pVariable), v);
			break;
		}
	}
}