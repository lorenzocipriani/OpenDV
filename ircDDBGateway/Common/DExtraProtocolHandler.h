/*
 *   Copyright (C) 2010-2013 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	DExtraProtocolHandler_H
#define	DExtraProtocolHandler_H

#include "UDPReaderWriter.h"
#include "DStarDefines.h"
#include "ConnectData.h"
#include "HeaderData.h"
#include "AMBEData.h"
#include "PollData.h"

#if defined(__WINDOWS__)
#include "Inaddr.h"
#else
#include <netinet/in.h>
#endif

#include <wx/wx.h>

enum DEXTRA_TYPE {
	DE_NONE,
	DE_HEADER,
	DE_AMBE,
	DE_POLL,
	DE_CONNECT
};

class CDExtraProtocolHandler {
public:
	CDExtraProtocolHandler(unsigned int port, const wxString& addr = wxEmptyString);
	~CDExtraProtocolHandler();

	bool open();

	unsigned int getPort() const;

	bool writeHeader(const CHeaderData& header);
	bool writeAMBE(const CAMBEData& data);
	bool writeConnect(const CConnectData& connect);
	bool writePoll(const CPollData& poll);

	DEXTRA_TYPE   read();
	CHeaderData*  readHeader();
	CAMBEData*    readAMBE();
	CPollData*    readPoll();
	CConnectData* readConnect();

	void close();

private:
	CUDPReaderWriter m_socket;
	DEXTRA_TYPE      m_type;
	unsigned char*   m_buffer;
	unsigned int     m_length;
	in_addr          m_yourAddress;
	unsigned int     m_yourPort;
	unsigned int     m_myPort;

	bool readPackets();
};

#endif
