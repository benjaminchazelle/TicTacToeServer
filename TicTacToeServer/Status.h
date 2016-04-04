enum Status {

	STATUS_OK,

	NONSENSE,

	//D�finir son pseudo
	CHOOSE_YOUR_NAME,
	PSEUDO_UNAVAILABLE,
	PSEUDO_NOT_RESPECT_THE_FORMAT,
	PSEUDO_ATTRIBUTED,

	//Obtenir son pseudo
	UNDEFINED_PSEUDO,
	OBTENTION_PSEUDO_SUCCESS,

	//Cr�er un match
	INVALID_PSEUDO,
	INVALID_GRID_SIZE,
	INVALID_WINSIZE,
	GAME_CREATED,

	//R�cup�rer la liste des matchs
	OTENTION_MATCH_SUCCESS,

	//R�cup�rer les informations d'un match
	MATCH_NOT_EXISTS_INFOS,
	OTENTION_INFOS_SUCCESS,

	//Pour rejoindre un match
	MATCH_NOT_EXISTS_JOIN,
	INCORRECT_MOD,
	GAME_FULL,
	IMPOSSIBILITY_JOIN,
	JOIN_GAME_SUCCESS,

	YOU_CAN_JOIN,

	//Pour jouer dans un match
	INVALID_COORDINATES,
	INVALID_CASE,
	GAME_FINISHED,
	NOT_UR_TURN,
	MOVE_DONE,

	OPPONENT_PLAYED,

	//Pour red�marrer un match
	MATH_NOT_EXISTS_RESET,
	GAME_RESTARTED,

	//Pour quitter un match
	MATH_NOT_EXISTS_QUIT,
	GAME_QUIT,

	//Pour conna�tre l'identit� d'un joueur
	PLAYER_NOT_EXISTS,
	INVALID_SYNTAX,
	GETID_SUCCESS

};