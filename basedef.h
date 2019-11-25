/*
 * 파일명 : basedef.h
 * 기능 : 모든 반환 값, 또는 심볼 값에 대한 정의
 * 수정 날짜 : 2019-11-25
 * 파일 제작자 : 세종대학교
 *				오픈소스개론[Pro.장문정] - Team5 (임정원, 강민성, 원성훈, 고선엽)
 */
#ifndef BASE_DEFINE
#define BASE_DEFINE

/* Define of array size */
#define A_SIZE 3  // Array size

/* Default number of return */
#define FALSE 0
#define TRUE 1

/*Define number of game point*/
#define WIN 10
#define LOSE -10
#define DRAW 0	

/*Define nuber of board check*/
enum { HUMAN, COMP, EMPTY };

/*Define number of level*/
#define EASY 100
#define NORMAL 200
#define HARD 300


/*Define ranking's element*/
struct ranking 
{
	float score;
	int status;
	int id;
};

#endif