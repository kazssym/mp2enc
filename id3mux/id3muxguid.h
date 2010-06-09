/*
 * ID3 Mux - DirectShow filter to add ID3 tags to audio streams.
 * Copyright (C) 2010 Kaz Sasa.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ID3MUXGUID_INCLUDED
#define ID3MUXGUID_INCLUDED 1

extern const GUID CLSID_Id3Mux;

// Uses struct to make C compatible.
struct __declspec(uuid("{571F34D1-09C9-4F87-9676-A013F5F701EF}")) TId3MuxImpl;

#ifdef INITGUID
const GUID CLSID_Id3Mux = __uuidof(TId3MuxImpl);
#endif

#endif
