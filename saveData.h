#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

#define NOMINMAX
#include "ShlObj.h"

namespace SaveData {

	inline int g_highscore{0};
	inline const std::string g_highscoreFileName{ "highscore.txt" };
	inline const std::string g_dataFolderName{ "WoolieInvaders" };

	inline static int ReadHighscoreFromDisk() {
		// Read saved high score.
		TCHAR windowsProgramDataPath[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, windowsProgramDataPath)))
		{
			std::wstring test{ windowsProgramDataPath }; //convert to wstring
			std::string test2{ test.begin(), test.end() }; //and convert to string.

			// Now load our file if possible.
			std::filesystem::path dataDirectoryPath{ test2 + "\\" + g_dataFolderName };
			if (std::filesystem::is_directory(dataDirectoryPath)) {
				// Check if file exists.
				std::filesystem::path highscoreFilePath{ dataDirectoryPath.string() + std::string{"\\" + g_highscoreFileName} };
				if (std::filesystem::exists(highscoreFilePath)) {
					// Open the file and read the first line.
					std::ifstream inf{ highscoreFilePath };
					std::string highScoreData{};
					std::getline(inf, highScoreData);
					int score{ std::stoi(highScoreData) };
					// TODO: Error handling!
					g_highscore = score;
				}
				else {
					std::cout << "No file: " << highscoreFilePath;
				}
			}
			else {
				std::cout << "No folder: " << dataDirectoryPath;
			}

		}
		return 0;
	}

	inline static void WriteHighscoreToDisk(int score) {
		g_highscore = score;

		TCHAR windowsProgramDataPath[MAX_PATH];
		if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, windowsProgramDataPath)))
		{
			return;
		}

		std::wstring test{ windowsProgramDataPath }; //convert to wstring
		std::string test2{ test.begin(), test.end() }; //and convert to string.

		// Woolie invaders directory.
		std::filesystem::path dataDirectoryPath{ test2 + "\\" + g_dataFolderName };
		if (!std::filesystem::is_directory(dataDirectoryPath)) {
			// Create directory.
			bool success = std::filesystem::create_directory(dataDirectoryPath);
		}

		std::filesystem::path highscoreFilePath{ dataDirectoryPath.string() + std::string{"\\" + g_highscoreFileName}};

		// Open (create and open if file doesn't exist) the file for writing.
		std::ofstream outFile{ highscoreFilePath };

		// If we couldn't open the output file stream for writing.
		if (!outFile)
		{
			std::cerr << "Uh oh, " << highscoreFilePath << " could not be opened for writing!\n";
			return;
		}

		// Write the new highscore to the file.
		outFile << score;

		// File closes once outf is out of scope.
	}
}