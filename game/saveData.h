#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>


namespace SaveData {

	inline int g_highscore{ 0 };
	inline const std::string g_highscoreFileName{ "highscore.txt" };
	inline const std::string g_dataFolderName{ "SaveData" };

	inline static void ReadHighscoreFromDisk() {
		// Read saved high score.

		// Now load our file if possible.
		std::filesystem::path dataDirectoryPath{ g_dataFolderName };
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
				std::cout << "Loaded highscore: " << score << " from " << highscoreFilePath << "\n";
				g_highscore = score;
			}
			else {
				std::cout << "No file: " << highscoreFilePath << "\n";
			}
		}
		else {
			std::cout << "No folder: " << dataDirectoryPath << "\n";
		}
	}

	inline static void WriteHighscoreToDisk(int score) {
		g_highscore = score;


		// SaveData directory.
		std::filesystem::path dataDirectoryPath{ g_dataFolderName };
		if (!std::filesystem::is_directory(dataDirectoryPath)) {
			// Create directory.
			bool success = std::filesystem::create_directory(dataDirectoryPath);
			if (!success) {
				std::cerr << "Failed to create directory: " << dataDirectoryPath << " Not saving highscore!\n";
				return;
			}
		}

		std::filesystem::path highscoreFilePath{ dataDirectoryPath.string() + std::string{"\\" + g_highscoreFileName} };

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
		std::cout << "Highscore of: " << score << " written to " << highscoreFilePath << "\n";
		// File closes once outf is out of scope.
	}
}