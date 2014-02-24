#include "jarvis.h"

Jarvis::Jarvis(QWidget *parent)
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

{
	this->_ui.setupUi(this);
	this->_settings = NULL;
	this->_voice = NULL;
	this->_continue = true;
	this->_settingsDialog = new VoiceSettingsDialog();
	this->initActionsConnections();
	this->initCommandsList();
	this->setAttribute(Qt::WA_DeleteOnClose, true);
}

Jarvis::~Jarvis()
{
	if (this->_settingsDialog)
		delete this->_settingsDialog;
	if (this->_session)
		this->_session->Release();
	if (this->_voice)
	{
		this->_voice->Close();
		this->_voice->Release();
	}
}

bool										Jarvis::initSDKSession()
{
	if (PXCSession_Create(&this->_session)<PXC_STATUS_NO_ERROR) {
		QMessageBox::critical(this, tr("Critical Intel SDK Error"), "Failed to create an SDK session");
		return false;
	}
	this->_settingsDialog->setSession(this->_session, _synth);
	return true;
}

bool										Jarvis::initVoicePipeLine()
{
	if (this->_voice->Init())
	{
		this->_voice->QueryCapture()->QueryDevice()->SetProperty(PXCCapture::Device::PROPERTY_AUDIO_MIX_LEVEL, 1.0f);
		return true;
	}
	return false;
}

bool										Jarvis::run()
{
	while (this->_continue)
	{
		if (this->_settings)
		{
			if (!this->_voice->AcquireFrame(true)) break;
			this->_voice->ReleaseFrame();
		}
		qApp->processEvents();
	}
	return true;
}

void										Jarvis::initActionsConnections()
{
	connect(this->_ui.actionExit, SIGNAL(triggered()),
		this, SLOT(prepareToQuit()));
	connect(this->_ui.actionVoiceSettings, SIGNAL(triggered()),
		_settingsDialog, SLOT(show()));
	connect(this->_settingsDialog, SIGNAL(settingsChanged(VoiceSettingsDialog::Settings *)),
		this, SLOT(setSettings(VoiceSettingsDialog::Settings *)));
}

void										Jarvis::initCommandsList()
{
	this->_cmds.push_back(std::wstring(L"Redémarre"));
	this->_cmds.push_back(std::wstring(L"Merci Jarvis"));
	this->_cmds.push_back(std::wstring(L"Va sur Google"));
	this->_cmds.push_back(std::wstring(L"Ouvre iTunes"));
	this->_cmds.push_back(std::wstring(L"Suce des queues"));
}

void										Jarvis::setSettings(VoiceSettingsDialog::Settings *settings)
{
	this->_settings = settings;
	this->_voice = new VoicePipeLine();

	qRegisterMetaType<PXCVoiceRecognition::Recognition>();
	connect(this->_voice, SIGNAL(voiceRecognized(PXCVoiceRecognition::Recognition )),
		this, SLOT(onVoiceRecognized(PXCVoiceRecognition::Recognition )), Qt::QueuedConnection);

	this->_voice->QueryCapture()->SetFilter((pxcCHAR*)this->_settings->source.toStdWString().c_str());
	this->_voice->EnableVoiceRecognition((pxcCHAR*)this->_settings->module.toStdWString().c_str());
	this->_voice->setProfileIndex(this->_settings->language);
	this->_voice->SetVoiceCommands(this->_cmds);
	if (this->initVoicePipeLine() != true)
		this->close();
}

void										Jarvis::onVoiceRecognized(PXCVoiceRecognition::Recognition data)
{
	qDebug() << "Jarvis Thread: " << QThread::currentThread();
	qDebug() << "recognition data size: " << sizeof(data);
	if (data.label<0)
	{
		//QString tmp = QString::fromStdWString(data.dictation);
		//if (QString::fromStdWString(data.dictation) == QString("Va sur Google"))
		//	QDesktopServices::openUrl(QUrl("http://www.google.com"));
		//else if (QString::fromStdWString(data.dictation) == QString("Suce des queues"))
		//	QDesktopServices::openUrl(QUrl("http://www.youporn.com"));
		//else if (QString::fromStdWString(data.dictation) == QString("Ouvre iTunes"))
		//	QProcess::startDetached(QString("C:\\Program Files (x86)\\iTunes\\iTunes.exe"), QStringList(), QString(""));
		//else if (QString::fromStdWString(data.dictation) == QString("Bonjour"))
		//	system("C:\\Windows\\System32\\shutdown /r /t 2");
		//else
			QMessageBox::information(NULL, "Voice Recognation", QString("Sentence recognized: "
			+ QString::fromWCharArray(data.dictation)));
	}
	else
	{
		for (int i = 0; i < sizeof(data.nBest) / sizeof(data.nBest[0]); i++)
		{
			if (data.nBest[i].label < 0 || data.nBest[i].confidence == 0)
				continue;
			QString tmp = "";
			if (data.nBest[i].label < this->_cmds.size())
				tmp = QString::fromStdWString(this->_cmds.at(data.nBest[i].label));
			if (tmp == QString("Va sur Google")) {
				QDesktopServices::openUrl(QUrl("http://www.google.com")); this->speak(L"Oui maitre");}
			else if (QString::fromStdWString(data.dictation) == QString("Ouvre iTunes"))
				QProcess::startDetached(QString("C:\\Program Files (x86)\\iTunes\\iTunes.exe"), QStringList(), QString(""));
			else if (QString::fromStdWString(data.dictation) == QString("Suce des queues")) {
				QDesktopServices::openUrl(QUrl("http://www.youporn.com")); this->speak(L"Et bien bravo mon salaud");}
			else if (QString::fromStdWString(data.dictation) == QString::fromStdWString(L"Redémarre")) {
				this->speak(L"Votre ordinateur va redémarrer dans une minute"); system("C:\\Windows\\System32\\shutdown /r /t 60"); }
			else if (QString::fromStdWString(data.dictation) == QString("Merci Jarvis")) {
				this->speak(L"Je vais maintenant m'eteindre"); this->prepareToQuit();}
			//else
			//QMessageBox::information(NULL, "Voice Recognation", QString("Sentence recognized: ")
			//+ QString::fromStdWString(this->_cmds.at(data.nBest[i].label)));
		}
	}
}

void										Jarvis::speak(pxcCHAR* sentence)
{
	PXCSession::ImplDesc desc;
	memset(&desc,0,sizeof(desc));
	pxcStatus sts= this->_session->CreateImpl<PXCVoiceSynthesis>(&desc,&this->_synth);
	if (sts<PXC_STATUS_NO_ERROR)
		return ;

	PXCVoiceSynthesis::ProfileInfo pinfo;
	sts=this->_synth->QueryProfile(this->_settings->language,&pinfo);
	sts=this->_synth->SetProfile(&pinfo);
	if (sts<PXC_STATUS_NO_ERROR)
		return ;

	pxcUID id=0;
	this->_synth->QueueSentence(sentence,sizeof(sentence)/sizeof(pxcCHAR),&id);

	VoiceOut vo(&pinfo);
	for (;;) {
	    PXCSmartSP sp;
		PXCAudio *sample;
        // Request audio data from TTS
        sts=this->_synth->ProcessAudioAsync(id, &sample, &sp);
		if (sts<PXC_STATUS_NO_ERROR) break;
        
        // Make sure there is data that is valid
        sts = sp->Synchronize();
        if (sts<PXC_STATUS_NO_ERROR) break;

        vo.RenderAudio(sample);
	}
}


void										Jarvis::closeEvent(QCloseEvent *event)
{
	this->prepareToQuit();
}

void										Jarvis::prepareToQuit()
{
	this->_continue = false;
	this->close();
}

