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

#ifndef VOICE_SETTINGS_DIALOG_H
#define VOICE_SETTINGS_DIALOG_H

#include <string>

#include <QtCore\QString>
#include <QDialog>
#include <QString>
#include "pxcvoice.h"
#include "util_capture.h"
#include "util_render.h"
#include "util_pipeline.h"

#include "defines.h"

#include "ui_voice_settings_dialog.h"

class PXCVoiceSynthesis;

class								VoiceSettingsDialog : public QDialog
{
	Q_OBJECT
public:
	struct Settings
	{
		QString						source;
		QString						module;
		int							language;
	};

private:
	Ui::VoiceSettingsDialog			_ui;
	PXCSession *					_session;
	Settings						_currentSettings;

public:
	VoiceSettingsDialog(QWidget *parent = 0);
	~VoiceSettingsDialog();

	const Settings					settings() const;
	PXCVoiceSynthesis *				setSession(PXCSession*, PXCVoiceSynthesis *);

private:
	void							initActionsConnections();
	PXCVoiceSynthesis *				populateSources(PXCVoiceSynthesis *);
	void							populateModules();
	void							populateLanguages();
	wchar_t *						LanguageToString(PXCVoiceRecognition::ProfileInfo::Language);
	void							updateSettings();

private slots:
	void							apply();

public: signals:
	void settingsChanged(VoiceSettingsDialog::Settings *newSettings);
};

Q_DECLARE_METATYPE(VoiceSettingsDialog::Settings*);

#endif //VOICE_SETTINGS_DIALOG_H