#include "TNDataStatistics.h"
#include <QJsonObject>
TNDataStatistics::TNDataStatistics(QObject *parent)
: QObject(parent), _httpDam(NULL)
{
}

TNDataStatistics::~TNDataStatistics()
{

}

TNDataStatistics* TNDataStatistics::GetInstance()
{
	static TNDataStatistics s_DataStatics(NULL);
	return &s_DataStatics;
}

void TNDataStatistics::RecordDamData(OPERATE_TYPE type, const TNPluginParamPtr &pluginParam)
{
	if (_httpDam == NULL)
		_httpDam = new TNHttpDam;
	_httpDam->RecordDeviceData(pluginParam, type);
}

void TNDataStatistics::RecordDamSearchData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam, const TNDamSearchData& searchData)
{
	if (_httpDam == NULL)
		_httpDam = new TNHttpDam;
	_httpDam->RecordSearchData(pluginParam, type, searchData);

}

void TNDataStatistics::RecordDamData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam)
{
	if (_httpDam == NULL)
		_httpDam = new TNHttpDam;
	_httpDam->RecordFunctionData(pluginParam, type);
}


void TNDataStatistics::CloseRecord()
{
	if (_httpDam)
		delete _httpDam;
	_httpDam = NULL;
}


void TNDataStatistics::RecordStatisData(OPERATE_TYPE type, const TNPluginParamPtr &pluginParam)
{
	
}

void TNDataStatistics::RecordFuncStatisData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam)
{
	
}

void TNDataStatistics::RecordSearchStaticsData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam, const TNDamSearchData& searchData)
{
	
}

void TNDataStatistics::CloseStatisData()
{
	TNDataStatistics::GetInstance()->CloseRecord();
}
