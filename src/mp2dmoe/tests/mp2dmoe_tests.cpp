/*
 * mp2dmoe_tests - unit test runner for mp2dmoe
 * Copyright (C) 2013  Kaz Sasa
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <System.hpp>
#pragma hdrstop

#include <GUITestRunner.hpp>
#include <tchar.h>

#pragma comment(lib, "msdmo")

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
        Application->Initialize();
        Guitestrunner::RunRegisteredTests();
    } catch (Exception &exception) {
        Application->ShowException(&exception);
    } catch (...) {
        try {
            throw Exception("");
        } catch (Exception &exception) {
            Application->ShowException(&exception);
        }
    }
    return 0;
}
