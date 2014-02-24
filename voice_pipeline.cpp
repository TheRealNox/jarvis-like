/*************************************************************************************************
Copyright 2014 Nicolas AUBRY

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*************************************************************************************************/

#include "voice_pipeline.h"

VoicePipeLine::VoicePipeLine() : UtilPipeline()
{
	EnableVoiceRecognition();
}

void	PXCAPI	VoicePipeLine::OnRecognized(PXCVoiceRecognition::Recognition *data)
{
	qDebug() << "VoicePipeLine Thread: " << QThread::currentThread();
	emit this->voiceRecognized(*data);
}

void			VoicePipeLine::OnVoiceRecognitionSetup(PXCVoiceRecognition::ProfileInfo *pinfo)
{
	QueryVoiceRecognition()->QueryProfile(this->_pidx,pinfo);
}

void			VoicePipeLine::setProfileIndex(int pidx)
{
	this->_pidx = pidx;
}

/*
Settings in correct order
QueryCapture()->SetFilter(L"Microphone (Realtek High Definition Audio)");
EnableVoiceRecognition(L"Voice Recognition (Nuance*)");
SetProfileIndex(?????);
SetVoiceCommands(std::vector<std::wstring> cmds);
*/