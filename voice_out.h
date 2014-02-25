/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include <Windows.h>
#include <vector>
#include "pxcvoice.h"
#include "singleton.hpp"

class VoiceOut {
protected:

	enum { buffering=3 };

	WAVEHDR				m_headers[buffering];
	PXCAudio::AudioData m_data[buffering];
	PXCAudio*			m_samples[buffering];

	int					m_nsamples;
	HWAVEOUT			m_hwo;

    WAVEFORMATEX		m_wfx;

public:

	VoiceOut(PXCVoiceSynthesis::ProfileInfo *pinfo) {
		m_nsamples=0;
		m_hwo=0;
		
		memset(&m_wfx,0,sizeof(m_wfx));
		m_wfx.wFormatTag=WAVE_FORMAT_PCM;
		m_wfx.nSamplesPerSec=pinfo->outputs.info.sampleRate;
		m_wfx.wBitsPerSample=16;
		m_wfx.nChannels=pinfo->outputs.info.nchannels;
		m_wfx.nBlockAlign=(m_wfx.wBitsPerSample/8)*m_wfx.nChannels;
		m_wfx.nAvgBytesPerSec=m_wfx.nBlockAlign*m_wfx.nSamplesPerSec;

		waveOutOpen(&m_hwo,WAVE_MAPPER,&m_wfx,0,0,CALLBACK_NULL);

        memset(&m_samples, 0, sizeof(m_samples));
	}

	void RenderAudio(PXCAudio *audio) {
		int k=(m_nsamples%buffering);
		if (m_nsamples++>=buffering) {
			while (waveOutUnprepareHeader(m_hwo,&m_headers[k],sizeof(WAVEHDR))==WAVERR_STILLPLAYING)
				Sleep(10);
			m_samples[k]->ReleaseAccess(&m_data[k]);
			m_samples[k]->Release();
		}
		m_samples[k]=audio;
		if (m_samples[k]->AcquireAccess(PXCAudio::ACCESS_READ,PXCAudio::AUDIO_FORMAT_PCM,&m_data[k])>=PXC_STATUS_NO_ERROR) {
			memset(&m_headers[k],0,sizeof(WAVEHDR));
			m_headers[k].dwBufferLength=m_data[k].dataSize*2;
			m_headers[k].lpData=(LPSTR)m_data[k].dataPtr;
			waveOutPrepareHeader(m_hwo,&m_headers[k],sizeof(WAVEHDR));
			waveOutWrite(m_hwo, &m_headers[k], sizeof(WAVEHDR));
		}
	}

	~VoiceOut(void) {
		if (!m_hwo || m_nsamples<=0) return;
		for (int i=m_nsamples-buffering;i<m_nsamples;i++) {
			int k=(i%buffering);
            if (m_samples[k])
            {
                while (waveOutUnprepareHeader(m_hwo,&m_headers[k],sizeof(WAVEHDR))==WAVERR_STILLPLAYING)
                    Sleep(10);
                m_samples[k]->ReleaseAccess(&m_data[k]);
                m_samples[k]->Release();
                m_samples[k]=0;
            }
		}
		waveOutClose(m_hwo);
	}
};

typedef Singleton<VoiceOut> VoiceOutSingleton;
