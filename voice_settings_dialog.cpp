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

#include "voice_settings_dialog.h"

VoiceSettingsDialog::VoiceSettingsDialog(QWidget *parent) :
	QDialog(parent)
{
	this->_ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	initActionsConnections();
}

VoiceSettingsDialog::~VoiceSettingsDialog()
{
}

VoiceSettingsDialog::Settings const			VoiceSettingsDialog::settings() const
{
	return this->_currentSettings;
}

PXCVoiceSynthesis *							VoiceSettingsDialog::setSession(PXCSession* session, PXCVoiceSynthesis * synth)
{
	this->_session = session;
	synth = this->populateSources(synth);
	this->populateModules();
	this->populateLanguages();
	return synth;
}

void										VoiceSettingsDialog::initActionsConnections()
{
	connect(_ui.okButton, SIGNAL(clicked()),
		this, SLOT(apply()));
	connect(_ui.okButton, SIGNAL(clicked()),
		this, SLOT(hide()));
}

PXCVoiceSynthesis *							VoiceSettingsDialog::populateSources(PXCVoiceSynthesis * synth)
{
	PXCSession::ImplDesc desc;
	memset(&desc,0,sizeof(desc));
	desc.group=PXCSession::IMPL_GROUP_SENSOR;
	desc.subgroup=PXCSession::IMPL_SUBGROUP_AUDIO_CAPTURE;
	for (int i=0,k=ID_SOURCEX;;i++)
	{
		PXCSession::ImplDesc desc1;
		if (this->_session->QueryImpl(&desc,i,&desc1)<PXC_STATUS_NO_ERROR)
			break;
		PXCSmartPtr<PXCCapture> capture;
		if (this->_session->CreateImpl<PXCCapture>(&desc1,&capture)<PXC_STATUS_NO_ERROR)
			continue;
		for (int j=0;;j++)
		{
			PXCCapture::DeviceInfo dinfo;
			if (capture->QueryDevice(j,&dinfo)<PXC_STATUS_NO_ERROR)
				break;
			this->_ui.sourceListBox->addItem(QString::fromWCharArray(dinfo.name), QVariant(k++));
		}
	}
	if (this->_session->CreateImpl<PXCVoiceSynthesis>(&desc,&synth)<PXC_STATUS_NO_ERROR)
		;
	return synth;
}

void										VoiceSettingsDialog::populateModules()
{
	PXCSession::ImplDesc desc, desc1;
	memset(&desc,0,sizeof(desc));
	desc.cuids[0]=PXCVoiceRecognition::CUID;
	int i;
	for (i=0;;i++)
	{
		if (this->_session->QueryImpl(&desc,i,&desc1)<PXC_STATUS_NO_ERROR) break;
		this->_ui.moduleListBox->addItem(QString::fromWCharArray(desc1.friendlyName), QVariant(ID_MODULEX+i));
	}
}

void										VoiceSettingsDialog::populateLanguages()
{
	HMENU menu1=CreatePopupMenu();
	PXCSession::ImplDesc desc, desc1;
	memset(&desc,0,sizeof(desc));
	desc.cuids[0]=PXCVoiceRecognition::CUID;
	PXCSmartPtr<PXCVoiceRecognition> vrec;
	if (this->_session->CreateImpl<PXCVoiceRecognition>(&desc1,&vrec)>=PXC_STATUS_NO_ERROR) {
		for (int k=0;;k++) {
			PXCVoiceRecognition::ProfileInfo pinfo;
			if (vrec->QueryProfile(k,&pinfo)<PXC_STATUS_NO_ERROR) break;
			QString tmp = QString::fromWCharArray(LanguageToString(pinfo.language));
			if (tmp != 0)
				this->_ui.languageListBox->addItem(tmp, QVariant(ID_LANGUAGEX+k));
			this->_ui.languageListBox->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
		}
	}
}

pxcCHAR *									VoiceSettingsDialog::LanguageToString(
	PXCVoiceRecognition::ProfileInfo::Language language)
{
	switch (language)
	{
		case PXCVoiceRecognition::ProfileInfo::LANGUAGE_US_ENGLISH:
			return L"US English";
		case PXCVoiceRecognition::ProfileInfo::LANGUAGE_FR_FRENCH:
			return L"Français";
	}
	return 0;
}

void										VoiceSettingsDialog::apply()
{
	this->updateSettings();
	emit settingsChanged(&this->_currentSettings);
	this->hide();
}

void										VoiceSettingsDialog::updateSettings()
{
	this->_currentSettings.source = this->_ui.sourceListBox->currentText();
	this->_currentSettings.module = this->_ui.moduleListBox->currentText();
	this->_currentSettings.language = this->_ui.languageListBox->currentIndex();
}
