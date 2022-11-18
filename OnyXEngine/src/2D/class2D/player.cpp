#include "../../../myIncludes/class2D/player.hpp"

Player::Player()
{
	return ;
}

Player::~Player()
{
	return ;
}

/***************************************** Init images ********************************************/

void	Player::ftInitImgsEd(void) // Edward Elrick
{
	// Idle
	this->p1_idle_ri[0] = LoadTexture("./imgs/edward_elric/ed_idle_ri/ed_idleri_00.png");
	this->p1_idle_ri[1] = LoadTexture("./imgs/edward_elric/ed_idle_ri/ed_idleri_01.png");
	this->p1_idle_ri[2] = LoadTexture("./imgs/edward_elric/ed_idle_ri/ed_idleri_02.png");
	this->p1_idle_ri[3] = LoadTexture("./imgs/edward_elric/ed_idle_ri/ed_idleri_03.png");

	this->p1_idle_lft[0] = LoadTexture("./imgs/edward_elric/ed_idle_lft/ed_idlelft_00.png");
	this->p1_idle_lft[1] = LoadTexture("./imgs/edward_elric/ed_idle_lft/ed_idlelft_01.png");
	this->p1_idle_lft[2] = LoadTexture("./imgs/edward_elric/ed_idle_lft/ed_idlelft_02.png");
	this->p1_idle_lft[3] = LoadTexture("./imgs/edward_elric/ed_idle_lft/ed_idlelft_03.png");

	// Jump
	this->p1_jumpr[0] = LoadTexture("./imgs/edward_elric/ed_jumpri/ed_jumpr_00.png");
	this->p1_jumpr[1] = LoadTexture("./imgs/edward_elric/ed_jumpri/ed_jumpr_01.png");

	this->p1_jumpl[0] = LoadTexture("./imgs/edward_elric/ed_jumplft/ed_jumpl_00.png");
	this->p1_jumpl[1] = LoadTexture("./imgs/edward_elric/ed_jumplft/ed_jumpl_01.png");

	// Fall
	this->p1_falll[0] = LoadTexture("./imgs/edward_elric/ed_falllft/ed_falll_00.png");
	this->p1_falll[1] = LoadTexture("./imgs/edward_elric/ed_falllft/ed_falll_01.png");

	this->p1_fallr[0] = LoadTexture("./imgs/edward_elric/ed_fallri/ed_fallr_00.png");
	this->p1_fallr[1] = LoadTexture("./imgs/edward_elric/ed_fallri/ed_fallr_01.png");

	// Move
	this->p1_runRi[0] = LoadTexture("./imgs/edward_elric/ed_run_right/ed_runr_00.png");
	this->p1_runRi[1] = LoadTexture("./imgs/edward_elric/ed_run_right/ed_runr_01.png");
	this->p1_runRi[2] = LoadTexture("./imgs/edward_elric/ed_run_right/ed_runr_02.png");
	this->p1_runRi[3] = LoadTexture("./imgs/edward_elric/ed_run_right/ed_runr_03.png");
	this->p1_runRi[4] = LoadTexture("./imgs/edward_elric/ed_run_right/ed_runr_04.png");
	this->p1_runRi[5] = LoadTexture("./imgs/edward_elric/ed_run_right/ed_runr_05.png");

	this->p1_runLft[0] = LoadTexture("./imgs/edward_elric/ed_run_lft/ed_runl_00.png");
	this->p1_runLft[1] = LoadTexture("./imgs/edward_elric/ed_run_lft/ed_runl_01.png");
	this->p1_runLft[2] = LoadTexture("./imgs/edward_elric/ed_run_lft/ed_runl_02.png");
	this->p1_runLft[3] = LoadTexture("./imgs/edward_elric/ed_run_lft/ed_runl_03.png");
	this->p1_runLft[4] = LoadTexture("./imgs/edward_elric/ed_run_lft/ed_runl_04.png");
	this->p1_runLft[5] = LoadTexture("./imgs/edward_elric/ed_run_lft/ed_runl_05.png");

	// Attack 00
	this->p1_attack00ri[0] = LoadTexture("./imgs/edward_elric/ed_attack_ri_00/ed_att_ri_00.png");
	this->p1_attack00ri[1] = LoadTexture("./imgs/edward_elric/ed_attack_ri_00/ed_att_ri_01.png");
	this->p1_attack00ri[2] = LoadTexture("./imgs/edward_elric/ed_attack_ri_00/ed_att_ri_02.png");
	this->p1_attack00ri[3] = LoadTexture("./imgs/edward_elric/ed_attack_ri_00/ed_att_ri_03.png");
	this->p1_attack00ri[4] = LoadTexture("./imgs/edward_elric/ed_attack_ri_00/ed_att_ri_04.png");
	this->p1_attack00ri[5] = LoadTexture("./imgs/edward_elric/ed_attack_ri_00/ed_att_ri_05.png");
	this->p1_attack00ri[6] = LoadTexture("./imgs/edward_elric/ed_attack_ri_00/ed_att_ri_06.png");

	this->p1_attack00lft[0] = LoadTexture("./imgs/edward_elric/ed_attack_lft_00/ed_att_lft_00.png");
	this->p1_attack00lft[1] = LoadTexture("./imgs/edward_elric/ed_attack_lft_00/ed_att_lft_01.png");
	this->p1_attack00lft[2] = LoadTexture("./imgs/edward_elric/ed_attack_lft_00/ed_att_lft_02.png");
	this->p1_attack00lft[3] = LoadTexture("./imgs/edward_elric/ed_attack_lft_00/ed_att_lft_03.png");
	this->p1_attack00lft[4] = LoadTexture("./imgs/edward_elric/ed_attack_lft_00/ed_att_lft_04.png");
	this->p1_attack00lft[5] = LoadTexture("./imgs/edward_elric/ed_attack_lft_00/ed_att_lft_05.png");
	this->p1_attack00lft[6] = LoadTexture("./imgs/edward_elric/ed_attack_lft_00/ed_att_lft_06.png");
}

void	Player::ftInitImgsIchigo(void) // Ichigo Kurosaki
{
	// Idle
	this->p1_idle_ri[0] = LoadTexture("./imgs/ichigo/ichigo_idleri/ichigo_idleri_00.png");
	this->p1_idle_ri[1] = LoadTexture("./imgs/ichigo/ichigo_idleri/ichigo_idleri_01.png");
	this->p1_idle_ri[2] = LoadTexture("./imgs/ichigo/ichigo_idleri/ichigo_idleri_02.png");
	this->p1_idle_ri[3] = LoadTexture("./imgs/ichigo/ichigo_idleri/ichigo_idleri_03.png");

	this->p1_idle_lft[0] = LoadTexture("./imgs/ichigo/ichigo_idlelft/ichigo_idlelft_00.png");
	this->p1_idle_lft[1] = LoadTexture("./imgs/ichigo/ichigo_idlelft/ichigo_idlelft_01.png");
	this->p1_idle_lft[2] = LoadTexture("./imgs/ichigo/ichigo_idlelft/ichigo_idlelft_02.png");
	this->p1_idle_lft[3] = LoadTexture("./imgs/ichigo/ichigo_idlelft/ichigo_idlelft_03.png");

	// Jump
	this->p1_jumpr[0] = LoadTexture("./imgs/ichigo/ichigo_jumpri/ichigo_jumpri_00.png");
	this->p1_jumpr[1] = LoadTexture("./imgs/ichigo/ichigo_jumpri/ichigo_jumpri_01.png");
	this->p1_jumpr[2] = LoadTexture("./imgs/ichigo/ichigo_jumpri/ichigo_jumpri_02.png");

	this->p1_jumpl[0] = LoadTexture("./imgs/ichigo/ichigo_jumplft/ichigo_jumplft_00.png");
	this->p1_jumpl[1] = LoadTexture("./imgs/ichigo/ichigo_jumplft/ichigo_jumplft_01.png");
	this->p1_jumpl[2] = LoadTexture("./imgs/ichigo/ichigo_jumplft/ichigo_jumplft_02.png");

	// Fall
	this->p1_falll[0] = LoadTexture("./imgs/ichigo/ichigo_falllft/ichigo_falllft_00.png");
	this->p1_falll[1] = LoadTexture("./imgs/ichigo/ichigo_falllft/ichigo_falllft_01.png");

	this->p1_fallr[0] = LoadTexture("./imgs/ichigo/ichigo_fallri/ichigo_fallri_00.png");
	this->p1_fallr[1] = LoadTexture("./imgs/ichigo/ichigo_fallri/ichigo_fallri_01.png");

	//Move
	this->p1_runRi[0] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_00.png");
	this->p1_runRi[1] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_01.png");
	this->p1_runRi[2] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_02.png");
	this->p1_runRi[3] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_03.png");
	this->p1_runRi[4] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_04.png");
	this->p1_runRi[5] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_05.png");
	this->p1_runRi[6] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_06.png");
	this->p1_runRi[7] = LoadTexture("./imgs/ichigo/ichigo_moveri/ichigo_moveri_07.png");

	this->p1_runLft[0] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_00.png");
	this->p1_runLft[1] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_01.png");
	this->p1_runLft[2] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_02.png");
	this->p1_runLft[3] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_03.png");
	this->p1_runLft[4] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_04.png");
	this->p1_runLft[5] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_05.png");
	this->p1_runLft[6] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_06.png");
	this->p1_runLft[7] = LoadTexture("./imgs/ichigo/ichigo_movelft/ichigo_movelft_07.png");

	// Attack 00
	this->p1_attack00ri[0] = LoadTexture("./imgs/ichigo/ichigo_attack_ri_00/ichigo_sa_ri_00.png");
	this->p1_attack00ri[1] = LoadTexture("./imgs/ichigo/ichigo_attack_ri_00/ichigo_sa_ri_01.png");
	this->p1_attack00ri[2] = LoadTexture("./imgs/ichigo/ichigo_attack_ri_00/ichigo_sa_ri_02.png");
	this->p1_attack00ri[3] = LoadTexture("./imgs/ichigo/ichigo_attack_ri_00/ichigo_sa_ri_03.png");
	this->p1_attack00ri[4] = LoadTexture("./imgs/ichigo/ichigo_attack_ri_00/ichigo_sa_ri_04.png");
	this->p1_attack00ri[5] = LoadTexture("./imgs/ichigo/ichigo_attack_ri_00/ichigo_sa_ri_05.png");
	this->p1_attack00ri[6] = LoadTexture("./imgs/ichigo/ichigo_attack_ri_00/ichigo_sa_ri_06.png");

	this->p1_attack00lft[0] = LoadTexture("./imgs/ichigo/ichigo_attack_lft_00/ichigo_sa_lft_00.png");
	this->p1_attack00lft[1] = LoadTexture("./imgs/ichigo/ichigo_attack_lft_00/ichigo_sa_lft_01.png");
	this->p1_attack00lft[2] = LoadTexture("./imgs/ichigo/ichigo_attack_lft_00/ichigo_sa_lft_02.png");
	this->p1_attack00lft[3] = LoadTexture("./imgs/ichigo/ichigo_attack_lft_00/ichigo_sa_lft_03.png");
	this->p1_attack00lft[4] = LoadTexture("./imgs/ichigo/ichigo_attack_lft_00/ichigo_sa_lft_04.png");
	this->p1_attack00lft[5] = LoadTexture("./imgs/ichigo/ichigo_attack_lft_00/ichigo_sa_lft_05.png");
	this->p1_attack00lft[6] = LoadTexture("./imgs/ichigo/ichigo_attack_lft_00/ichigo_sa_lft_06.png");
}

void Player::ftInitImgsMeliodas(void) // Meliodas Lostvayne
{
	// Idle
	this->p1_idle_ri[0] = LoadTexture("./imgs/meliodas/idle_ri/meliodas_idle_ri_00.png");
	this->p1_idle_ri[1] = LoadTexture("./imgs/meliodas/idle_ri/meliodas_idle_ri_01.png");

	this->p1_idle_lft[0] = LoadTexture("./imgs/meliodas/idle_lft/meliodas_idle_lft_00.png");
	this->p1_idle_lft[1] = LoadTexture("./imgs/meliodas/idle_lft/meliodas_idle_lft_01.png");

	// Jump
	this->p1_jumpr[0] = LoadTexture("./imgs/meliodas/jump_ri/meliodas_jump_ri_00.png");
	this->p1_jumpr[1] = LoadTexture("./imgs/meliodas/jump_ri/meliodas_jump_ri_01.png");

	this->p1_jumpl[0] = LoadTexture("./imgs/meliodas/jump_lft/meliodas_jump_lft_00.png");
	this->p1_jumpl[1] = LoadTexture("./imgs/meliodas/jump_lft/meliodas_jump_lft_01.png");

	// Fall
	this->p1_fallr[0] = LoadTexture("./imgs/meliodas/jump_ri/meliodas_jump_ri_00.png");
	// this->p1_fallr[1] = LoadTexture("./imgs/meliodas/jump_ri/meliodas_jump_ri_01.png");

	this->p1_falll[0] = LoadTexture("./imgs/meliodas/jump_lft/meliodas_jump_lft_00.png");
	// this->p1_falll[1] = LoadTexture("./imgs/meliodas/jump_lft/meliodas_jump_lft_01.png");

	// Move
	this->p1_runRi[0] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_00.png");
	this->p1_runRi[1] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_01.png");
	this->p1_runRi[2] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_02.png");
	this->p1_runRi[3] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_03.png");
	this->p1_runRi[4] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_04.png");
	this->p1_runRi[5] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_05.png");
	this->p1_runRi[6] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_06.png");
	this->p1_runRi[7] = LoadTexture("./imgs/meliodas/move_ri/meliodas_move_ri_07.png");

	this->p1_runLft[0] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_00.png");
	this->p1_runLft[1] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_01.png");
	this->p1_runLft[2] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_02.png");
	this->p1_runLft[3] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_03.png");
	this->p1_runLft[4] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_04.png");
	this->p1_runLft[5] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_05.png");
	this->p1_runLft[6] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_06.png");
	this->p1_runLft[7] = LoadTexture("./imgs/meliodas/move_lft/meliodas_move_lft_07.png");

	// Attack 00
	this->p1_attack00ri[0] = LoadTexture("./imgs/meliodas/attack_00_ri/meliodas_attack_00_ri_00.png");
	this->p1_attack00ri[1] = LoadTexture("./imgs/meliodas/attack_00_ri/meliodas_attack_00_ri_01.png");
	this->p1_attack00ri[2] = LoadTexture("./imgs/meliodas/attack_00_ri/meliodas_attack_00_ri_02.png");
	this->p1_attack00ri[3] = LoadTexture("./imgs/meliodas/attack_00_ri/meliodas_attack_00_ri_03.png");

	this->p1_attack00lft[0] = LoadTexture("./imgs/meliodas/attack_00_lft/meliodas_attack_00_lft_00.png");
	this->p1_attack00lft[1] = LoadTexture("./imgs/meliodas/attack_00_lft/meliodas_attack_00_lft_01.png");
	this->p1_attack00lft[2] = LoadTexture("./imgs/meliodas/attack_00_lft/meliodas_attack_00_lft_02.png");
	this->p1_attack00lft[3] = LoadTexture("./imgs/meliodas/attack_00_lft/meliodas_attack_00_lft_03.png");
}

/**************************************** Destroy images *******************************************/

void	Player::ftDestroyImgs1()
{
	UnloadTexture(this->p1_idle_ri[0]);
	UnloadTexture(this->p1_idle_ri[1]);
	UnloadTexture(this->p1_idle_ri[2]);
	UnloadTexture(this->p1_idle_ri[3]);

	UnloadTexture(this->p1_idle_lft[0]);
	UnloadTexture(this->p1_idle_lft[1]);
	UnloadTexture(this->p1_idle_lft[2]);
	UnloadTexture(this->p1_idle_lft[3]);

	UnloadTexture(this->p1_jumpr[0]);
	UnloadTexture(this->p1_jumpr[1]);

	UnloadTexture(this->p1_jumpl[0]);
	UnloadTexture(this->p1_jumpl[1]);

	UnloadTexture(this->p1_fallr[0]);
	UnloadTexture(this->p1_fallr[1]);

	UnloadTexture(this->p1_falll[0]);
	UnloadTexture(this->p1_falll[1]);

	UnloadTexture(this->p1_runRi[0]);
	UnloadTexture(this->p1_runRi[1]);
	UnloadTexture(this->p1_runRi[2]);
	UnloadTexture(this->p1_runRi[3]);
	UnloadTexture(this->p1_runRi[4]);
	UnloadTexture(this->p1_runRi[5]);

	UnloadTexture(this->p1_runLft[0]);
	UnloadTexture(this->p1_runLft[1]);
	UnloadTexture(this->p1_runLft[2]);
	UnloadTexture(this->p1_runLft[3]);
	UnloadTexture(this->p1_runLft[4]);
	UnloadTexture(this->p1_runLft[5]);
	UnloadTexture(this->p1_runLft[6]);

	UnloadTexture(this->p1_attack00ri[0]);
	UnloadTexture(this->p1_attack00ri[1]);
	UnloadTexture(this->p1_attack00ri[2]);
	UnloadTexture(this->p1_attack00ri[3]);
	UnloadTexture(this->p1_attack00ri[4]);
	UnloadTexture(this->p1_attack00ri[5]);
	UnloadTexture(this->p1_attack00ri[6]);

	UnloadTexture(this->p1_attack00lft[0]);
	UnloadTexture(this->p1_attack00lft[1]);
	UnloadTexture(this->p1_attack00lft[2]);
	UnloadTexture(this->p1_attack00lft[3]);
	UnloadTexture(this->p1_attack00lft[4]);
	UnloadTexture(this->p1_attack00lft[5]);
	UnloadTexture(this->p1_attack00lft[6]);
}

void	Player::ftDestroyImgs2()
{
	UnloadTexture(this->p1_idle_ri[0]);
	UnloadTexture(this->p1_idle_ri[1]);
	UnloadTexture(this->p1_idle_ri[2]);
	UnloadTexture(this->p1_idle_ri[3]);

	UnloadTexture(this->p1_idle_lft[0]);
	UnloadTexture(this->p1_idle_lft[1]);
	UnloadTexture(this->p1_idle_lft[2]);
	UnloadTexture(this->p1_idle_lft[3]);

	UnloadTexture(this->p1_jumpr[0]);
	UnloadTexture(this->p1_jumpr[1]);
	UnloadTexture(this->p1_jumpr[2]);

	UnloadTexture(this->p1_jumpl[0]);
	UnloadTexture(this->p1_jumpl[1]);
	UnloadTexture(this->p1_jumpl[2]);

	UnloadTexture(this->p1_fallr[0]);
	UnloadTexture(this->p1_fallr[1]);

	UnloadTexture(this->p1_falll[0]);
	UnloadTexture(this->p1_falll[1]);

	UnloadTexture(this->p1_runRi[0]);
	UnloadTexture(this->p1_runRi[1]);
	UnloadTexture(this->p1_runRi[2]);
	UnloadTexture(this->p1_runRi[3]);
	UnloadTexture(this->p1_runRi[4]);
	UnloadTexture(this->p1_runRi[5]);
	UnloadTexture(this->p1_runRi[6]);
	UnloadTexture(this->p1_runRi[7]);

	UnloadTexture(this->p1_runLft[0]);
	UnloadTexture(this->p1_runLft[1]);
	UnloadTexture(this->p1_runLft[2]);
	UnloadTexture(this->p1_runLft[3]);
	UnloadTexture(this->p1_runLft[4]);
	UnloadTexture(this->p1_runLft[5]);
	UnloadTexture(this->p1_runLft[6]);
	UnloadTexture(this->p1_runLft[7]);

	UnloadTexture(this->p1_attack00ri[0]);
	UnloadTexture(this->p1_attack00ri[1]);
	UnloadTexture(this->p1_attack00ri[2]);
	UnloadTexture(this->p1_attack00ri[3]);
	UnloadTexture(this->p1_attack00ri[4]);
	UnloadTexture(this->p1_attack00ri[5]);
	UnloadTexture(this->p1_attack00ri[6]);

	UnloadTexture(this->p1_attack00lft[0]);
	UnloadTexture(this->p1_attack00lft[1]);
	UnloadTexture(this->p1_attack00lft[2]);
	UnloadTexture(this->p1_attack00lft[3]);
	UnloadTexture(this->p1_attack00lft[4]);
	UnloadTexture(this->p1_attack00lft[5]);
	UnloadTexture(this->p1_attack00lft[6]);
}

void	Player::ftDestroyImgs3(void)
{
	UnloadTexture(this->p1_idle_ri[0]);
	UnloadTexture(this->p1_idle_ri[1]);

	UnloadTexture(this->p1_idle_lft[0]);
	UnloadTexture(this->p1_idle_lft[1]);

	UnloadTexture(this->p1_jumpr[0]);
	UnloadTexture(this->p1_jumpr[1]);

	UnloadTexture(this->p1_jumpl[0]);
	UnloadTexture(this->p1_jumpl[1]);

	UnloadTexture(this->p1_fallr[0]);

	UnloadTexture(this->p1_falll[0]);

	UnloadTexture(this->p1_runRi[0]);
	UnloadTexture(this->p1_runRi[1]);
	UnloadTexture(this->p1_runRi[2]);
	UnloadTexture(this->p1_runRi[3]);
	UnloadTexture(this->p1_runRi[4]);
	UnloadTexture(this->p1_runRi[5]);
	UnloadTexture(this->p1_runRi[6]);
	UnloadTexture(this->p1_runRi[7]);

	UnloadTexture(this->p1_runLft[0]);
	UnloadTexture(this->p1_runLft[1]);
	UnloadTexture(this->p1_runLft[2]);
	UnloadTexture(this->p1_runLft[3]);
	UnloadTexture(this->p1_runLft[4]);
	UnloadTexture(this->p1_runLft[5]);
	UnloadTexture(this->p1_runLft[6]);
	UnloadTexture(this->p1_runLft[7]);

	UnloadTexture(this->p1_attack00ri[0]);
	UnloadTexture(this->p1_attack00ri[1]);
	UnloadTexture(this->p1_attack00ri[2]);
	UnloadTexture(this->p1_attack00ri[3]);

	UnloadTexture(this->p1_attack00lft[0]);
	UnloadTexture(this->p1_attack00lft[1]);
	UnloadTexture(this->p1_attack00lft[2]);
	UnloadTexture(this->p1_attack00lft[3]);
}

/**************************************** Gestion images *******************************************/

Texture2D	Player::ftReturnGoodImage(std::string string, int ct)
{
	if (string == "Idle Lft")
		return (this->p1_idle_lft[ct]);
	else if (string == "Idle Ri")
		return (this->p1_idle_ri[ct]);
	else if (string == "Move Ri")
		return (this->p1_runRi[ct]);
	else if (string == "Move Lft")
		return (this->p1_runLft[ct]);
	else if (string == "Jump Ri")
		return (this->p1_jumpr[ct]);
	else if (string == "Jump Lft")
		return (this->p1_jumpl[ct]);
	else if (string == "Fall Ri")
		return (this->p1_fallr[ct]);
	else if (string == "Fall Lft")
		return (this->p1_falll[ct]);
	else if (string == "Attack 00 Lft")
		return (this->p1_attack00lft[ct]);
	else if (string == "Attack 00 Ri")
		return (this->p1_attack00ri[ct]);
	return (this->p1_idle_ri[0]);
}

void	Player::ftInitPlayerImgs(int nbr)
{
	if (nbr == 1) // Edward
	{
		this->ftInitImgsEd();
		this->nbr = nbr;
	}
	else if (nbr == 2) // Ichigo
	{
		this->ftInitImgsIchigo();
		this->nbr = nbr;
	}
	else if (nbr == 3) // Meliodas
	{
		this->ftInitImgsMeliodas();
		this->nbr = nbr;
	}
}

/**************************************** Collision Box ********************************************/

void	Player::ftSetCollosionBox(Vector2 pos, Vector2 size, Vector2 ajust)
{
	this->_varsSideDownPanel.collisionBox.x = pos.x;
	this->_varsSideDownPanel.collisionBox.y = pos.y;
	this->_varsSideDownPanel.collisionBox.width = size.x;
	this->_varsSideDownPanel.collisionBox.height = size.y;
	this->adjustCollBox.x = ajust.x;
	this->adjustCollBox.y = ajust.y;
}

void	Player::ftInitRectanglePlayer(Vector2 pos, Vector2 size)
{
	this->_varsSideDownPanel._playerBox.x = pos.x;
	this->_varsSideDownPanel._playerBox.y = pos.y;
	this->_varsSideDownPanel._playerBox.width = size.x;
	this->_varsSideDownPanel._playerBox.height = size.y;
}

float	Player::ftReturnAjustCollBox(char c) const
{
	if (c == 'X')
		return (this->adjustCollBox.x);
	if (c == 'Y')
		return (this->adjustCollBox.y);
	return (0);
}

Rectangle	Player::ftReturnRectangleCollBox(void) const
{
	return (this->_varsSideDownPanel.collisionBox);
}

Rectangle	Player::FtReturnRectanglePlayer(void) const
{
	return (this->_varsSideDownPanel._playerBox);
}

Rectangle	Player::ftReturnCollisionBox(void) const
{
	return (this->_varsSideDownPanel.collisionBox);
}

void	Player::ftChangeCollisionBoxSize(Vector2 pos)
{
	this->_varsSideDownPanel.collisionBox.width = pos.x;
	this->_varsSideDownPanel.collisionBox.height = pos.y;
}

void	Player::ftMoveCollisionBox(Vector2 pos)
{
	this->_varsSideDownPanel.collisionBox.x += pos.x;
	this->_varsSideDownPanel.collisionBox.y += pos.y;
}

int		Player::ftReturnCollBoxPos(char c) const
{
	if (c == 'X')
		return (this->_varsSideDownPanel.collisionBox.x);
	else if (c == 'Y')
		return (this->_varsSideDownPanel.collisionBox.y);
	return (0);
}

int		Player::ftReturnCollBoxSize(char c) const
{
	if (c == 'W')
		return (this->_varsSideDownPanel.collisionBox.width);
	else if (c == 'H')
		return (this->_varsSideDownPanel.collisionBox.height);
	return (0);
}

void	Player::ftSetAjustCollBox(Vector2 pos)
{
	this->adjustCollBox.x = pos.x;
	this->adjustCollBox.y = pos.y;
}
/******************************************** Weapon ***********************************************/

void	Player::ftInitWeapon(std::string name, Vector2 pos, Vector2 size)
{
	// Weapon	weapon = new Weapon;

	this->_weapon.ftInitWeapon(name, pos, size);
	// this->_weapon = weapon;
}

// Return //

Rectangle	Player::ftReturnWeaponCollRect(void) const
{
	return (this->_weapon.ftReturnWeaponCollRect());
}

Vector2		Player::ftReturnAjustCollisionBox(void) const
{
	return (this->adjustCollBox);
}

float	Player::ftReturnWeaponCollBoxPos(char c) const
{
	return (this->_weapon.ftReturnCollBoxPos(c));
}

float	Player::ftReturnWeaponCollBoxSize(char c) const
{
	return (this->_weapon.ftReturnCollBoxSize(c));
}

float	Player::ftReturnWeaponDamage(void) const
{
	return (this->_weapon.ftReturnWeaponDamage());
}

float	Player::ftReturnAddWeaponDamage(void) const
{
	return (this->_weapon.ftReturnAddWeaponDamage());
}

std::string	Player::ftReturnWeaponName(void) const
{
	return (this->_weapon.ftReturnName());
}

// Change //

void	Player::ftChangeWeaponCollBoxPos(float pos,char c)
{
	this->_weapon.ftChangeCollBoxPos(pos, c);
}

void	Player::ftNewWeaponCollBoxPos(float pos,char c)
{
	this->_weapon.ftNewCollBoxPos(pos, c);
}

void	Player::ftChangeWeaponCollBoxSize(float size,char c)
{
	this->_weapon.ftChangeCollBoxSize(size, c);
}

void	Player::ftChangeWeaponDamage(float damage)
{
	this->_weapon.ftChangeWeaponDamage(damage);
}

void	Player::ftAddWeaponDamage(float damage)
{
	this->_weapon.ftAddWeaponDamage(damage);
}

/***************************************** Player Stats ********************************************/

Vector2		Player::ftReturnCollisionBoxPos(void) const
{
	return ((Vector2){this->_varsSideDownPanel.collisionBox.width,
		this->_varsSideDownPanel.collisionBox.height});
}

Player	*Player::ftReturnPlayer(void)
{
	Player *ret = new Player;
	ret = this;

	return (ret);
}

VarChar		*Player::ftReturnVarsChar(void)
{
	return (&this->_varsSideDownPanel.varChar);
}

SelectionBoxPly	*Player::ftSelectionBoxPly(void)
{
	return (&this->_selectionBox);
}

void		Player::ftInitVarChar(void)
{
	this->_varsSideDownPanel.varChar.plyPosX = (char *)calloc(sizeof(char), 9);
	this->_varsSideDownPanel.varChar.plyPosY = (char *)calloc(sizeof(char), 9);
	this->_varsSideDownPanel.varChar.plyWidth = (char *)calloc(sizeof(char), 9);
	this->_varsSideDownPanel.varChar.plyHeight = (char *)calloc(sizeof(char), 9);
	this->_varsSideDownPanel.varChar.collBoxPosX = (char *)calloc(sizeof(char), 9);
	this->_varsSideDownPanel.varChar.collBoxPosY = (char *)calloc(sizeof(char), 9);
	this->_varsSideDownPanel.varChar.collBoxWidth = (char *)calloc(sizeof(char), 9);
	this->_varsSideDownPanel.varChar.collBoxHeight = (char *)calloc(sizeof(char), 9);
}

void		Player::ftDeleteVarChar(void)
{
	free(this->_varsSideDownPanel.varChar.plyPosX);
	free(this->_varsSideDownPanel.varChar.plyPosY);
	free(this->_varsSideDownPanel.varChar.plyWidth);
	free(this->_varsSideDownPanel.varChar.plyHeight);
	free(this->_varsSideDownPanel.varChar.collBoxPosX);
	free(this->_varsSideDownPanel.varChar.collBoxPosY);
	free(this->_varsSideDownPanel.varChar.collBoxWidth);
	free(this->_varsSideDownPanel.varChar.collBoxHeight);
}

void    Player::ftSetPosition(Vector2 pos)
{
	this->position = pos;
	this->_varsSideDownPanel.collisionBox.x = pos.x;
	this->_varsSideDownPanel.collisionBox.y = pos.y;
	this->_varsSideDownPanel._playerBox.x = pos.x;
	this->_varsSideDownPanel._playerBox.y = pos.y;
}

void    Player::ftChangePosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
	this->_varsSideDownPanel.collisionBox.x = x;
	this->_varsSideDownPanel.collisionBox.y = y;
	this->_varsSideDownPanel._playerBox.x = x;
	this->_varsSideDownPanel._playerBox.y = y;
}

void    Player::ftMovePosition(float x, float y)
{
	this->position.x += x;
	this->position.y += y;
	this->_varsSideDownPanel.collisionBox.x += x;
	this->_varsSideDownPanel.collisionBox.y += y;
	this->_varsSideDownPanel._playerBox.x += x;
	this->_varsSideDownPanel._playerBox.y += y;
}

Vector2 Player::ftReturnPlayerPosition(void)
{
	return(this->position);
}

Vector2 *Player::ftReturnPlayerPositionPtr(void)
{
	return(&this->position);
}

float   Player::ftReturnPlayerPositionX(void)
{
    return (this->position.x);
}

float   Player::ftReturnPlayerPositionY(void)
{
    return (this->position.y);
}

float	Player::ftReturnSpeed(void)
{
	return (this->speed);
}

bool	Player::ftReturnJump(void)
{
	return (this->canJump);
}

void	Player::ftChangeSpeed(float speed)
{
	this->speed += speed;
}

void	Player::ftSetSpeed(float speed)
{
	this->speed = speed;
}

void	Player::ftChangeJump(bool jump)
{
	this->canJump = jump;
}

int		Player::ftReturnFace(void) const
{
	return (this->face);
}

int		Player::ftReturnCt(void) const
{
	return (this->ct);
}

void	Player::ftChangeCt(int ct)
{
	this->ct = ct;
}

int		Player::ftReturnAttackCt(void) const
{
	return (this->ctA);
}

void	Player::ftChangeAttackCt(int ct)
{
	this->ctA = ct;
}

void	Player::ftChangeFace(int face)
{
	this->face = face;
}

int		Player::ftReturnCtIdle(void) const
{
	return (this->ctIdle);
}

void	Player::ftChangeCtIdle(int ct)
{
	this->ctIdle = ct;
}

int		Player::ftReturnCtMove(void) const
{
	return (this->ctMove);
}

void	Player::ftChangeCtMove(int ct)
{
	this->ctMove = ct;
}

int		Player::ftReturnCtJump(void) const
{
	return (this->ctJump);
}

void	Player::ftChangeCtJump(int ct)
{
	this->ctJump = ct;
}

int		Player::ftReturnCtFall(void) const
{
	return (this->ctFall);
}

void	Player::ftChangeCtFall(int ct)
{
	this->ctFall = ct;
}

int		Player::ftReturnCtAttack(void) const
{
	return (this->ctAttack);
}

void	Player::ftChangeCtAttack(int ct)
{
	this->ctAttack = ct;
}

void	Player::ftInitCtMoveX(int ct)
{
	this->moveX = ct;
}

void	Player::ftInitCtMoveY(int ct, std::string string)
{
	if (string == "Idle")
		this->moveIdleY = ct;
	else if (string == "Move")
		this->moveMoveY = ct;
}

int		Player::ftReturnCtMoveX(void) const
{
	return (this->moveX);
}

int		Player::ftReturnctMoveY(std::string string) const
{
	if (string == "Idle")
		return (this->moveIdleY);
	else if (string == "Move")
		return (this->moveMoveY);
	return (0);
}

int		Player::ftReturnMoveAttackLftX(void) const
{
	return (this->moveAttackLftX);
}

void	Player::ftChangeMoveAttackLftX(int ct)
{
	this->moveAttackLftX = ct;
}

int		Player::ftReturnMoveAttackRiX(void) const
{
	return (this->moveAttackRiX);
}

void	Player::ftChangeMoveAttackRiX(int ct)
{
	this->moveAttackRiX = ct;
}

int		Player::ftReturnMoveAttackY(void) const
{
	return (this->moveAttackY);
}

void	Player::ftChangeMoveAttackY(int ct)
{
	this->moveAttackY = ct;
}

int		Player::ftReturnMoveIdleX(void) const
{
	return (this->moveIdleX);
}

void	Player::ftChangeMoveIdleX(int ct)
{
	this->moveIdleX = ct;
}

float	Player::ftReturnLastY(void) const
{
	return (this->lastY);
}

void	Player::ftChangeLastY(int ct)
{
	this->lastY = ct;
}

int		Player::ftReturnNbr(void) const
{
	return (this->nbr);
}

bool	Player::ftReturnDoAttack(void) const
{
	return (this->doAttack);
}

void	Player::ftChangeDoAttack(bool ct)
{
	this->doAttack = ct;
}

bool	Player::ftReturnCollX(void) const
{
	return (this->collX);
}

void	Player::ftChangeCollX(bool ct)
{
	this->collX = ct;
}
