#pragma once


namespace oglElements {

	enum eConfigType :int32 {
		eString   = 0,
		eInt32    = 1,
		eFloat32  = 2,
		eVector3f = 3,
	};


	class StrKeyValue {
	public:
		std::string name;
		std::string value;
	};

	class ConfigRecord {
	public:

		ConfigRecord();
		ConfigRecord(std::string _name, eConfigType t, void* pVar);
		ConfigRecord(std::string _name, eConfigType t, const void* pVar);

		std::string name;
		eConfigType	type;
		void		*pVariable;
	};


	/*
	Setting file

		format:

		each line is a setting key value pair in text seperated by :

		<settingName1> : <settingvalue1>
		<settingName2> : <settingvalue2>
	*/
	class SettingFile {
	public:

		void setSettings(const std::vector<ConfigRecord>& records);

		bool load(const std::string &filePath);

		bool save(const std::string& filePath);

	private:

		ConfigRecord* getConfig(const std::string& key);

		void setConfigValue(ConfigRecord* var, const std::string& value);

		std::vector<ConfigRecord> varList;
	};
}