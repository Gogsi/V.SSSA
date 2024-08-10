#include "utils.h"

std::uint32_t joaat(const char* string) {
	return joaatc(string, std::strlen(string));
}

std::uint32_t joaat(const std::string& string)
{
	return joaatc(string.c_str(), string.size());
}

int ShowTheFeedNotification(const char* text) {
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	return HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(1, 1);
}

void ShowHelpText(const char* text) {
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, false, true, 5000);
}

void ShowHelpText(const char* text1, const char* text2) {
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("TWOSTRINGS");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text1);
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text2);
	HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, false, true, 5000);
}

void ShowHelpText(const char* text1, const char* text2, const char* text3) {
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("THREESTRINGS");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text1);
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text2);
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text3);
	HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, false, true, 5000);
}