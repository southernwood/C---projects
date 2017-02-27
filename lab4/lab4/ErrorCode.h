#ifndef ERRORCODE_H
#define ERRORCODE_H

enum funReturn {

	success = 0,
	file_open_failed = 1,
	command_line_wrong,
	cannot_read_line = 3,
	cannot_extract_dimension = 4,
	cannot_extract_game_piece_info = 5,
	fail_find_wellDefinitioned_piece = 6,
	size_vertor_not_match = 7,
	input_error,
	ask_to_quit,
	quit_the_game,
	game_draw,
	bad_alloc,
	alreay_has_game,
	can_not_save_file,
	no_data_found,
	can_not_win=99,

};

enum arrayIndex{

	functionName = 0,
	gameName = 1,
	commandNumber = 2,
	autocommandNumber = 3,
	selectcommandNumber =4,
};

#endif
