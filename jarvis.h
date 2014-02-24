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

#ifndef JARVIS_H
#define JARVIS_H

#include <QtWidgets/QMainWindow>

#include <QMessageBox>
#include <QLabel>
#include <QProcess>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDesktopServices>
#include <QMetaType>
#include <QUrl>
#include "ui_jarvis.h"
#include "voice_out.h"
#include "voice_pipeline.h"
#include "voice_settings_dialog.h"

class								Jarvis : public QMainWindow
{
	Q_OBJECT

private:
	Ui::JarvisClass					_ui;
	VoicePipeLine *					_voice;
	VoiceSettingsDialog	*			_settingsDialog;
	VoiceSettingsDialog::Settings * _settings;
	PXCSession *					_session;
	PXCVoiceSynthesis *				_synth;
	std::vector<std::wstring>		_cmds;
	bool							_continue;

public:
	Jarvis(QWidget *parent = 0);
	~Jarvis();
	bool							initSDKSession();
	bool							initVoicePipeLine();
	bool							run();
	void							closeEvent(QCloseEvent*);

private:
	void							initActionsConnections();
	void							initCommandsList();
	void							speak(pxcCHAR*);

public slots:
	void							setSettings(VoiceSettingsDialog::Settings*);
	void							onVoiceRecognized(PXCVoiceRecognition::Recognition data);

private slots:
	void							prepareToQuit();
};

#endif // JARVIS_H
