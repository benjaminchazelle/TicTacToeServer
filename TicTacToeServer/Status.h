#ifndef STATUSH
#define STATUSH

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Enum�ration permettant de g�rer les diff�rentes erreurs//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum Status {



	NONSENSE,




	MATCH_EVER_STARTED_OR_FINISHED,
	MATCH_PLAYER_IS_NOT_PARTICIPANT,
	INVALID_INVITATION,
	MATCH_NOT_PLAYED_BY_CURRENT_PLAYER,
	MATCH_INVALID_STROKE,
	PARTICIPANT_ADDED,
	MATCH_NOT_STARTED,
	MATCH_STROKE_DONE,
	MATCH_NOT_EXISTS,
	MATCH_USER_ALREADY_INNER,
	MATCH_USER_ACCEPTED,
	MATCH_NOT_ENOUGH_PLACE,
	PLAYER_NOT_EXISTS,
	MATCH_NOT_INVITED,
	MATCH_INCORRECT_STROKE,
	MATCH_UNAVAILABLE_CASE,
	MATCH_RESETED,
	MATCH_DESERTED,
	MATCH_PLAYER_ALREADY_DESERTED
};

#endif