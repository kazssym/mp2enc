/*
 * MP2 Encoder DMO.
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

#ifndef MP2GUID_INCLUDED
#define MP2GUID_INCLUDED 1

extern const GUID CLSID_Mp2Encoder;

// Uses struct to make C compatible.
struct __declspec(uuid("{3FCD30F6-88FE-4A44-A518-1DBB0937DAE4}")) TMp2EncoderImpl;

#ifdef INITGUID
const GUID CLSID_Mp2Encoder = __uuidof(TMp2EncoderImpl);
#endif

#endif
