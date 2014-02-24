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

#ifndef VOICE_PIPELINE_H
#define VOICE_PIPELINE_H

#include "util_render.h"
#include "util_pipeline.h"
#include <QObject>
#include <QMessageBox>
#include <QMetaType>
#include <QtDebug>
#include <QThread>
#include <assert.h>

class							VoicePipeLine : public QObject, public UtilPipeline
{

	Q_OBJECT

private:
	int							_pidx;

public:
	VoicePipeLine();
	virtual void	PXCAPI		OnRecognized(PXCVoiceRecognition::Recognition *data);
	virtual void				OnVoiceRecognitionSetup(PXCVoiceRecognition::ProfileInfo *pinfo);
	void						setProfileIndex(int);
private:

public: signals:
	void						voiceRecognized(PXCVoiceRecognition::Recognition data);
};

Q_DECLARE_METATYPE(PXCVoiceRecognition::Recognition)


#endif //VOICE_PIPELINE_H