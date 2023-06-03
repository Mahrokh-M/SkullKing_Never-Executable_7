#include "History.h"
History::History() {
	opponent_score = "";
	user_score = "";
	opponent_score = "";
}
History::History(string opponent_username, string opponent_score, string user_score) {
	this->opponent_username = opponent_username;
	this->opponent_score = opponent_score;
	this->user_score = user_score;
}
string History::get_opponent_username() {
	return opponent_username;
}
string History::get_opponent_score() {
	return opponent_score;
}
string History::get_user_score() {
	return user_score;
}