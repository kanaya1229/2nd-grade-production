#include "ExploreScene.h"
#include "DxLib.h"
#include "SaveData.h"
#include "UIButton.h"

// ベッド
Button bedButton(
	520, 520,
	340, 120);

// 机
Button deskButton(
	1280, 460,
	560, 320);

// 本棚
Button bookshelfButton(
	1030, 120,
	300, 560);

// ドア
Button doorButton(
	0, 400,
	220, 520);

// 左のドア（研究室）
Button labDoorButton(
	1420, 300,
	140, 450);

// 右のドア（倉庫）
Button storageDoorButton(
	1570, 170,
	260, 650);

// 奥の張り紙
Button noteButton(
	1050, 400,
	160, 300);

// 左下の本
Button fairyBookButton(
	260, 650,
	260, 180);

// 右棚の防毒マスク
Button maskButton(
	1410, 120,
	300, 260);

// 右下のホース
Button hoseButton(
	1430, 620,
	420, 180);

// 左の出口
Button backHallFromLabButton(
	0, 120,
	180, 760);

// 左棚
Button diaryButton(
	80, 80,
	500, 900);

// 右棚
Button pamButton(
	1340, 80,
	500, 900);

// 奥棚
Button fireDocButton(
	690, 120,
	560, 500);

// 戻る
Button backHallFromStorageButton(
	760, 900,
	400, 120);

// 状態

int roomBG[4];

int selectIndex = 0;

const int MAX_CHOICES = 10;

const char* choices[MAX_CHOICES];

int choiceCount = 0;

char message[2048] = "";

bool IsMouseClickRect(int x, int y, int w, int h)
{
	int mx, my;

	GetMousePoint(&mx, &my);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
		mx >= x &&
		mx <= x + w &&
		my >= y &&
		my <= y + h)
	{
		return true;
	}

	return false;
}

void DamagePlayer(int damage, const char* text)
{
	player.hp -= damage;

	if (player.hp < 0)
	{
		player.hp = 0;
	}

	strcpy_s(message, text);
}

void SetChoices_FirstRoom()
{
	choiceCount = 0;

	choices[choiceCount++] = "ベッド";
	choices[choiceCount++] = "机";
	choices[choiceCount++] = "本棚";
	choices[choiceCount++] = "扉";
}

void SetChoices_Hall()
{
	choiceCount = 0;

	choices[choiceCount++] = "研究室";
	choices[choiceCount++] = "倉庫";
	choices[choiceCount++] = "奥の扉";
}

void SetChoices_Lab()
{
	choiceCount = 0;

	choices[choiceCount++] = "机";
	choices[choiceCount++] = "棚";
	choices[choiceCount++] = "シンク";
	choices[choiceCount++] = "廊下へ戻る";
}

void SetChoices_Storage()
{
	choiceCount = 0;

	choices[choiceCount++] = "左の棚";
	choices[choiceCount++] = "右の棚";
	choices[choiceCount++] = "奥の棚";
	choices[choiceCount++] = "廊下へ戻る";
}

void InitExploreScene()
{
	player.currentRoom = ROOM_FIRST;

	selectIndex = 0;

	strcpy_s(message,
		"苦しい。\n"
		"息が出来ない。");

	roomBG[ROOM_FIRST] = LoadGraph("Image\\firstroom.png");
	roomBG[ROOM_HALL] = LoadGraph("Image\\hall.png");
	roomBG[ROOM_LAB] = LoadGraph("Image\\lab.png");
	roomBG[ROOM_STORAGE] = LoadGraph("Image\\storage.png");

	SetChoices_FirstRoom();
}

void Update_FirstRoom()
{
	// ベッド
	if (bedButton.IsClicked())
	{
		if (!player.checkedBed)
		{
			strcpy_s(message,
				"古びたベッドだ。\n"
				"あまり清潔には見えない。");

			player.checkedBed = true;
		}
		else
		{
			strcpy_s(message,
				"もう調べた。");
		}
	}

	// 机
	if (deskButton.IsClicked())
	{
		if (!player.checkedDesk)
		{
			strcpy_s(message,
				"大量の書類が積まれている。");

			player.checkedDesk = true;
		}
		else
		{
			strcpy_s(message,
				"もう調べた。");
		}
	}

	// 本棚
	if (bookshelfButton.IsClicked())
	{
		if (!player.checkedBookshelf)
		{
			strcpy_s(message,
				"リンについての本が並んでいる。");

			player.checkedBookshelf = true;
		}
		else
		{
			strcpy_s(message,
				"もう調べた。");
		}
	}

	// ドア
	if (doorButton.IsClicked())
	{
		player.currentRoom = ROOM_HALL;

		strcpy_s(message,
			"白熱灯に照らされた廊下だ。");

		SetChoices_Hall();

		DamagePlayer(1,
			"息苦しい。\n"
			"肺が焼けるように痛む。");
	}
}

void Update_Hall()
{
	// 研究室
	if (labDoorButton.IsClicked())
	{
		player.currentRoom = ROOM_LAB;

		strcpy_s(message,
			"研究室のようだ。");
	}

	// 倉庫
	if (storageDoorButton.IsClicked())
	{
		player.currentRoom = ROOM_STORAGE;

		strcpy_s(message,
			"倉庫のようだ。");
	}

	// 張り紙
	if (noteButton.IsClicked())
	{
		strcpy_s(message,
			"『必ずマスクを着用』と書かれている。");
	}
}

void Update_Lab()
{
	// 絵本
	if (fairyBookButton.IsClicked())
	{
		if (player.checkedFairyBook)
		{
			strcpy_s(message,
				"もう読んだ絵本だ。");
		}
		else
		{
			strcpy_s(message,
				"『マッチ売りの少女』の絵本だ。");

			player.checkedFairyBook = true;
		}
	}

	// 防毒マスク
	if (maskButton.IsClicked())
	{
		if (player.checkedMask)
		{
			strcpy_s(message,
				"もう持って行った。");
		}
		else
		{
			player.hasMask = true;
			player.checkedMask = true;

			strcpy_s(message,
				"防毒マスクを手に入れた。");
		}
	}

	// ホース
	if (hoseButton.IsClicked())
	{
		if (player.checkedHose)
		{
			strcpy_s(message,
				"もう持って行った。");
		}
		else
		{
			player.hasHose = true;
			player.checkedHose = true;

			strcpy_s(message,
				"長いホースが置かれている。");
		}
	}

	// 廊下へ戻る
	if (backHallFromLabButton.IsClicked())
	{
		player.currentRoom = ROOM_HALL;

		strcpy_s(message,
			"廊下へ戻った。");
	}
}

void Update_Storage()
{
	// 日記
	if (diaryButton.IsClicked())
	{
		if (player.checkedDiary)
		{
			strcpy_s(message,
				"もう読んでいる。");
		}
		else
		{
			player.checkedDiary = true;

			DamagePlayer(2,
				"吐き気がする。\n"
				"頭が痛い。");
		}
	}

	// PAM注射
	if (pamButton.IsClicked())
	{
		if (player.checkedPam)
		{
			strcpy_s(message,
				"もう空になっている。");
		}
		else
		{
			player.checkedPam = true;

			player.hp += 3;

			strcpy_s(message,
				"PAM注射を見つけた。");
		}
	}

	// 消火資料
	if (fireDocButton.IsClicked())
	{
		if (player.checkedFireDoc)
		{
			strcpy_s(message,
				"もう読んでいる。");
		}
		else
		{
			player.checkedFireDoc = true;

			strcpy_s(message,
				"消火についての資料がある。");
		}
	}

	// 廊下へ戻る
	if (backHallFromStorageButton.IsClicked())
	{
		player.currentRoom = ROOM_HALL;

		strcpy_s(message,
			"廊下へ戻った。");
	}
}

void UpdateExploreScene()
{
	switch (player.currentRoom)
	{
	case ROOM_FIRST:
		Update_FirstRoom();
		break;

	case ROOM_HALL:
		Update_Hall();
		break;

	case ROOM_LAB:
		Update_Lab();
		break;

	case ROOM_STORAGE:
		Update_Storage();
		break;
	}

	// 死亡
	if (player.hp <= 0)
	{
		strcpy_s(message,
			"呼吸が出来ない。\n"
			"視界が暗く閉ざされていく。");
	}
}

void DrawChoices()
{
	for (int i = 0; i < choiceCount; i++)
	{
		int y = 120 + i * 55;

		if (i == selectIndex)
		{
			DrawFormatString(
				1350,
				y,
				GetColor(0, 255, 0),
				"%s",
				choices[i]);
		}
		else
		{
			DrawFormatString(
				1350,
				y,
				GetColor(120, 120, 120),
				"%s",
				choices[i]);
		}
	}
}

void DrawMessageBox()
{
	DrawBox(
		40,
		760,
		1880,
		1040,
		GetColor(20, 20, 20),
		TRUE);

	DrawString(
		80,
		800,
		message,
		GetColor(255, 255, 255));
}

void DrawStatus()
{
	DrawFormatString(
		60,
		60,
		GetColor(255, 255, 255),
		"HP : %d",
		player.hp);
}

void DrawRoomName()
{
	switch (player.currentRoom)
	{
	case ROOM_FIRST:

		DrawString(
			60,
			20,
			"寝室",
			GetColor(255, 255, 255));

		break;

	case ROOM_HALL:

		DrawString(
			60,
			20,
			"廊下",
			GetColor(255, 255, 255));

		break;

	case ROOM_LAB:

		DrawString(
			60,
			20,
			"研究室",
			GetColor(255, 255, 255));

		break;

	case ROOM_STORAGE:

		DrawString(
			60,
			20,
			"倉庫",
			GetColor(255, 255, 255));

		break;
	}
}

void DrawExploreScene()
{
	DrawExtendGraph(
		0,
		0,
		1920,
		1080,
		roomBG[player.currentRoom],
		TRUE);


	DrawRoomName();

	DrawStatus();

	DrawMessageBox();

	switch (player.currentRoom)
	{
	case ROOM_FIRST:

		bedButton.DrawArea();
		deskButton.DrawArea();
		bookshelfButton.DrawArea();
		doorButton.DrawArea();

		bedButton.DrawLabel("ベッド");
		deskButton.DrawLabel("机");
		bookshelfButton.DrawLabel("本棚");
		doorButton.DrawLabel("扉");

		break;

	case ROOM_HALL:

		labDoorButton.DrawArea();
		storageDoorButton.DrawArea();
		noteButton.DrawArea();

		labDoorButton.DrawLabel("研究室");
		storageDoorButton.DrawLabel("倉庫");
		noteButton.DrawLabel("張り紙");

		break;
	case ROOM_LAB:

		fairyBookButton.DrawArea();
		maskButton.DrawArea();
		hoseButton.DrawArea();
		backHallFromLabButton.DrawArea();

		fairyBookButton.DrawLabel("絵本");
		maskButton.DrawLabel("防毒マスク");
		hoseButton.DrawLabel("ホース");
		backHallFromLabButton.DrawLabel("廊下へ戻る");

		break;

	case ROOM_STORAGE:

		diaryButton.DrawArea();
		pamButton.DrawArea();
		fireDocButton.DrawArea();
		backHallFromStorageButton.DrawArea();

		diaryButton.DrawLabel("古い日記");
		pamButton.DrawLabel("PAM注射");
		fireDocButton.DrawLabel("消火資料");
		backHallFromStorageButton.DrawLabel("廊下へ戻る");

		break;
	}
}