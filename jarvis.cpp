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

#include "jarvis.h"

Jarvis::Jarvis(QWidget *parent)
{
	this->_ui.setupUi(this);
	this->_settings = NULL;
	this->_voice = NULL;
	this->_continue = true;
	this->_settingsDialog = new VoiceSettingsDialog();
	this->initActionsConnections();
	this->initCommandsList();
	this->setAttribute(Qt::WA_DeleteOnClose, true);
	this->showMinimized();
	this->_settingsDialog->show();
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
	this->_cmds.push_back(std::wstring(L"�teindre"));
	this->_cmds.push_back(std::wstring(L"Red�marre"));
	this->_cmds.push_back(std::wstring(L"Annule le red�marrage"));
	this->_cmds.push_back(std::wstring(L"Merci Jarvis"));
	this->_cmds.push_back(std::wstring(L"Va sur Google"));
	this->_cmds.push_back(std::wstring(L"Ouvre iTunes"));
	this->_cmds.push_back(std::wstring(L"Vid�o en ligne"));
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

	// TODO:
	// Thread every actions to be taken in order to free the voice pipeline asap
	//

	qDebug() << "Jarvis Thread: " << QThread::currentThread();
	qDebug() << "recognition data size: " << sizeof(data);
	if (data.label<0)
	{
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
				QDesktopServices::openUrl(QUrl("http://www.google.com")); this->speak(L"Oui maitre"); break;}
			else if (QString::fromStdWString(data.dictation) == QString("Ouvre iTunes")) {
				QProcess::startDetached(QString("C:\\Program Files (x86)\\iTunes\\iTunes.exe"), QStringList(), QString("")); this->speak(L"Let's grouve tounaillte!"); break;}
			else if (QString::fromStdWString(data.dictation) == QString("Vid�o en ligne")) {
				QDesktopServices::openUrl(QUrl("http://www.youtube.com")); this->speak(L"Et bien bravo mon salaud"); break;}
			else if (QString::fromStdWString(data.dictation) == QString::fromStdWString(L"Annule le red�marrage")) {
				this->speak(L"Red�marrage annul�"); system("C:\\Windows\\System32\\shutdown /a");  break;}
			else if (QString::fromStdWString(data.dictation) == QString::fromStdWString(L"Red�marre")) {
				this->speak(L"Votre ordinateur va red�marrer dans une minute"); system("C:\\Windows\\System32\\shutdown /r /t 60");  break;}
			else if (QString::fromStdWString(data.dictation) == QString::fromStdWString(L"�teindre")) {
				this->speak(L"Votre ordinateur va s'�teindre dans 10 secondes"); system("C:\\Windows\\System32\\shutdown /s /t 10");  break;}
			else if (QString::fromStdWString(data.dictation) == QString("Merci Jarvis")) {
				this->speak(L"Je vais maintenant m'�teindre"); this->prepareToQuit(); break;}
			//else
			//QMessageBox::information(NULL, "Voice Recognation", QString("Sentence recognized: ")
			//+ QString::fromStdWString(this->_cmds.at(data.nBest[i].label)));
		}
	}
}

// TODO
// Thread Singleton
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

