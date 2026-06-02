#include "ExploreScene.h"
#include "DxLib.h"
#include "SaveData.h"
#include "UIButton.h"
#include < stdlib.h >
#include "SceneManager.h"

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
// 本棚の中身１
Button chemistryBookButton(
	1030, 300,
	250, 80);
// 2
Button pictureBookButton(
	1030, 420,
	250, 80);
// 閉じる
Button closeBookshelfButton(
	1030, 540,
	250, 80);

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

const char* roomName[] =
{
	"寝室",
	"廊下",
	"研究室",
	"倉庫"
};

// 状態
int roomBG[4];

bool showMemo = false;

char message[2048] = "";

int memoSelect = 0;

bool showMemoDetail = false;

int LastDice = 0;
bool showDice = false;
bool firstRoomExitReady = false;

Memo memo[50];

MemoType currentMemo = MEMO_NONE;

int RollDice(int max)
{
	return rand() % max + 1;
}

bool IsAllExploreFinished()
{
	return
		player.checkedBed &&
		player.checkedDesk &&
		player.checkedBookshelf &&
		player.checkedFairyBook &&
		player.hasMask &&
		player.hasHose &&
		player.checkedDiary &&
		player.hasPAM &&
		player.checkedFireDoc;
}

bool SkillCheck(int skill)
{
	LastDice = RollDice(6);
	showDice = true;

	return LastDice <= skill;
}

void DamagePlayer(int damage)
{
	player.hp -= damage;

	if (player.hp < 0)
	{
		player.hp = 0;
	}
}

void ChangeRoom(RoomType room, const char* text)
{
	int damage = RollDice(2);
	
	DamagePlayer(damage);

	player.currentRoom = room;

	sprintf_s(message,
		"%s\n\n"
		"息苦しさが増した。\n"
		"D2 → %d\n"
		"HP -%d",
		text,
		damage,
		damage);
}

void InitExploreScene()
{
	player.currentRoom = ROOM_FIRST;

	strcpy_s(message,
		"服が濡れているな。\n"
		"妙に息が苦しいような気がする....\n"
		"記憶の最後に持っていたものがすべてなくなっているな。");

	roomBG[ROOM_FIRST] = LoadGraph("Image\\firstroom.png");
	roomBG[ROOM_HALL] = LoadGraph("Image\\hall.png");
	roomBG[ROOM_LAB] = LoadGraph("Image\\lab.png");
	roomBG[ROOM_STORAGE] = LoadGraph("Image\\storage.png");

}

void Update_FirstRoom()
{
	// ベッド
	if (bedButton.IsClicked())
	{
		if (!player.checkedBed)
		{
			player.checkedBed = true;

			bool success = SkillCheck(player.insight);

			if (success)
			{
				sprintf_s(message,
					"洞察判定\n"
					"D6 → %d\n\n"
					"成功！\n\n"
					"古びたベッドだ。\n"
					"あまり清潔には見えない。\n"
					"\n"
					"台車の近くに車輪の痕がある。\n"
					"痕は扉の前まで続いている。",
					LastDice);
			}
			else
			{
				sprintf_s(message,
					"洞察判定\n"
					"D6 → %d\n\n"
					"失敗...\n\n"
					"古びたベッドだ。\n"
					"あまり清潔には見えない。\n"
					"\n"
					"近くには台車が置かれている。",
					LastDice);
			}
		}
		else
		{
			strcpy_s(message,
				"もうここは調べても意味がないだろう。");
		}
	}

	// 机
	if (deskButton.IsClicked())
	{
		// 初回説明
		if (!player.checkedDesk)
		{
			strcpy_s(message,
				"大量の書類が積まれている。\n"
				"マグカップが置かれている。\n"
				"\n"
				"書類を調べられそうだ。\n"
				"クリックで最大3回まで調査できる。");

			player.checkedDesk = true;
		}
		else
		{

			if (player.deskSearchCount == 3 &&
				!player.foundLeftMemo)
			{
				bool success = SkillCheck(player.insight);

				if (success)
				{
					player.foundLeftMemo = true;

					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"\n【追加発見】\n"
						"『左部』と書かれた付箋が貼られている。",
						LastDice);
				}
				else
				{
					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"失敗...\n"
						"特に気になるものはなかった。",
						LastDice);
				}

				return;
			}

			if (player.deskSearchCount >= 3)
			{
				strcpy_s(message,
					"もう十分調べた。");
				return;
			}

			player.deskSearchCount++;

			bool success = SkillCheck(player.knw);

			if (!success)
			{
				char temp[256];

				int n = 3 - player.deskSearchCount;

				if (n < 0) n = 0;

				sprintf_s(temp,
					"知識判定\n"
					"D6 → %d\n\n"
					"失敗...\n"
					"有用な資料は見つからなかった。\n\n"
					"残り調査回数:%d",
					LastDice,
					n);

				strcpy_s(message, temp);
			}
			else
			{
				if (!player.readDoc1 && player.deskSearchCount == 1)
				{
					player.readDoc1 = true;

					sprintf_s(message,
						"知識判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"【資料①】\n"
						"リンは『賢者の石』と呼ばれていた。",
						LastDice);
				}
				else if (!player.readDoc2 && player.deskSearchCount == 2)
				{
					player.readDoc2 = true;

					sprintf_s(message,
						"知識判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"【資料②】\n"
						"燃える石。",
						LastDice);
				}
				else if (!player.readDoc3 && player.deskSearchCount == 3)
				{
					player.readDoc3 = true;

					sprintf_s(message,
						"知識判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"【資料③】\n"
						"マッチ売りの少女はリン中毒だった！？\n"
						"\nまだ何か置いてあるようだ。",
						LastDice);
				}
			}
		}
	}

	if (bookshelfButton.IsClicked())
	{
		if (!player.checkedBookshelf)
		{
			player.checkedBookshelf = true;

			if (SkillCheck(player.knw))
			{
				player.readPhosphorus = true;

				sprintf_s(message,
					"知識判定\n"
					"D6 → %d\n\n"
					"成功！\n"
					"本棚のリンについての本が目に留まった。\n"
					"リンは人間が初めて実験で発見した元素。\n"
					"元素記号はP、原子番号は15。\n"
					"酸素に触れると青白く光る。\n"
					"他の本を確認してみよう。",
					LastDice);
			}
			else
			{
				sprintf_s(message,
					"知識判定\n"
					"D6 → %d\n\n"
					"失敗...\n"
					"化学の本が大量に並んでいる。\n"
					"最下段には絵本も置かれている。\n"
					"他の本を確認してみよう。",LastDice);
			}
		}
		else {
			strcpy_s(message,
				"本棚をまた確認しよう。");
		}

		player.bookshelfMenu = true;
	}

	if (player.bookshelfMenu)
	{
		if (chemistryBookButton.IsClicked())
		{
			if (!player.checkedChemBook)
			{
				player.checkedChemBook = true;

				if (SkillCheck(player.knw))
				{
					sprintf_s(message,
						"知識判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"『リンと生命』\n"
						"著：左部 優\n\n"
						"リンは有限な地下資源であり、"
						"生物にとって必要不可欠な元素である。",
						LastDice);
				}
				else
				{
					sprintf_s(message,
						"知識判定\n"
						"D6 → %d\n\n"
						"失敗...\n"
						"リンについて内容が難しく理解できない。",
						LastDice);
				}
			}
			else
			{
				strcpy_s(message,
					"先ほど読んだ本だ。");
			}
		}
		

		if (pictureBookButton.IsClicked())
		{
			if (!player.checkedPictureBook)
			{
				player.checkedPictureBook = true;

				if (SkillCheck(player.insight))
				{
					player.foundGap = true;

					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"どの絵本も新品同様だ。\n"
						"最下段に不自然な隙間を見つけた。\n"
						"まだ何かあるような気がする.....",
						LastDice);
				}
				else
				{
					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"失敗...\n"
						"様々な絵本が並んでいる。",
						LastDice);
				}
			}
			else if (player.foundGap && !player.foundMissingBook)
			{
				if (SkillCheck(player.insight))
				{
					player.foundMissingBook = true;

					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"隙間は中途半端な位置にある。\n"
						"本来ここに本があったのかもしれない。",
						LastDice);
				}
			}
			else {
				strcpy_s(message,
					"先ほど読んだ本だ。");
			}
		}

		if (closeBookshelfButton.IsClicked())
		{
			player.bookshelfMenu = false;

			strcpy_s(message,
				"もう見るところはないはずだろう。");
		}

		return;
	}

	if (doorButton.IsClicked())
	{
		if (!firstRoomExitReady)
		{
			firstRoomExitReady = true;

			strcpy_s(message,
				"一度他の部屋の探索をする必要がありそうだ...");
		}
		else
		{

			firstRoomExitReady = false;
			ChangeRoom(
				ROOM_HALL,
				message);
		}
	}
}

void Update_Hall()
{
	if (labDoorButton.IsClicked())
	{
		ChangeRoom(
			ROOM_LAB,
			"研究室のようだ。");
	}

	if (storageDoorButton.IsClicked())
	{
		ChangeRoom(
			ROOM_STORAGE,
			"倉庫のようだ。");
	}

	if (noteButton.IsClicked())
	{
		// 初回
		if (!player.bossDoorReady)
		{
			player.bossDoorReady = true;

			strcpy_s(message,
				"『必ずマスクを着用』と書かれている。\n"
				"異様な雰囲気を漂わせている。\n"
				"\n"
				"扉をこじ開けられそうだ...");
		}

		// 開放済み
		else if (player.canEnterBossRoom)
		{
			currentScene = SCENE_GAMEFIGHT;
		}

		// 全探索済みなら自動開放
		else if (IsAllExploreFinished())
		{
			player.canEnterBossRoom = true;

			strcpy_s(message,
				"必要な探索は終わった。\n"
				"扉の先へ進めそうだ。");
		}

		// 器用判定
		else
		{
			bool success = SkillCheck(player.tec);

			if (success)
			{
				player.canEnterBossRoom = true;

				sprintf_s(message,
					"器用判定\n"
					"D6 → %d\n\n"
					"成功！\n"
					"扉をこじ開けた。\n"
					"もう一度調べれば先へ進める。",
					LastDice);
			}
			else
			{
				sprintf_s(message,
					"器用判定\n"
					"D6 → %d\n\n"
					"失敗...\n"
					"扉は開かなかった。",
					LastDice);
			}
		}
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
			player.readFairyBook = true;
		}
	}

	// 防毒マスク
	if (maskButton.IsClicked())
	{
		if (player.hasMask)
		{
			strcpy_s(message,
				"もう持って行った。");
		}
		else
		{
			player.hasMask = true;
			
			strcpy_s(message,
				"防毒マスクを手に入れた。");
		}
	}

	// ホース
	if (hoseButton.IsClicked())
	{
		if (player.hasHose)
		{
			strcpy_s(message,
				"もう持って行った。");
		}
		else
		{
			player.hasHose = true;
			
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
			player.readDiary = true;
		}
	}

	// PAM注射
	if (pamButton.IsClicked())
	{
		if (player.hasPAM)
		{
			strcpy_s(message,
				"もう空になっている。");
		}
		else
		{
			player.hasPAM = true;
			
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
			player.readFireDoc = true;
			strcpy_s(message,
				"消火についての資料がある。");
		}
	}

	// 廊下へ戻る
	if (backHallFromStorageButton.IsClicked())
	{

		ChangeRoom(
			ROOM_HALL,
			"廊下へ戻った。");
	}
}

void UpdateExploreScene()
{
	if (IsKeyPressedOnce(KEY_INPUT_TAB))
	{
		showMemo = !showMemo;
	}

	if (showMemo)
	{
		return;
	}

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

	if (player.hp <= 0)
	{
		strcpy_s(message,
			"呼吸が出来ない。\n"
			"視界が暗く閉ざされていく。");
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
	DrawString(
		60,
		20,
		roomName[player.currentRoom],
		GetColor(255, 255, 255));
}

void DrawMemo()
{
	DrawBox(
		250,
		120,
		1670,
		960,
		GetColor(20, 20, 20),
		TRUE);

	DrawBox(
		250,
		120,
		1670,
		960,
		GetColor(255, 255, 255),
		FALSE);

	DrawString(
		300,
		150,
		"調査メモ",
		GetColor(255, 255, 255));
	int y = 240;

	DrawString(
		300,
		y,
		"【情報】",
		GetColor(255, 255, 0));

	y += 60;

	if (player.readPhosphorus)
	{
		DrawString(
			320,
			y,
			"・リンについて",
			GetColor(255, 255, 255));

		y += 40;
	}

	if (player.readFairyBook)
	{
		DrawString(
			320,
			y,
			"・マッチ売りの少女",
			GetColor(255, 255, 255));

		y += 40;
	}

	if (player.readDiary)
	{
		DrawString(
			320,
			y,
			"・古い日記",
			GetColor(255, 255, 255));

		y += 40;
	}

	if (player.readFireDoc)
	{
		DrawString(
			320,
			y,
			"・消火資料",
			GetColor(255, 255, 255));

		y += 40;
	}
	y += 50;

	DrawString(
		300,
		y,
		"【アイテム】",
		GetColor(0, 255, 255));

	y += 60;

	if (player.hasMask)
	{
		DrawString(
			320,
			y,
			"・防毒マスク",
			GetColor(255, 255, 255));

		y += 40;
	}

	if (player.hasHose)
	{
		DrawString(
			320,
			y,
			"・ホース",
			GetColor(255, 255, 255));

		y += 40;
	}

	if (player.hasPAM)
	{
		DrawString(
			320,
			y,
			"・PAM注射",
			GetColor(255, 255, 255));

		y += 40;
	}

	if (showMemo)
	{
		if (IsKeyPressedOnce(KEY_INPUT_UP))
		{
			memoSelect--;
		}

		if (IsKeyPressedOnce(KEY_INPUT_DOWN))
		{
			memoSelect++;
		}

		if (IsKeyPressedOnce(KEY_INPUT_RETURN))
		{
			showMemoDetail = true;
		}

		if (IsKeyPressedOnce(KEY_INPUT_ESCAPE))
		{
			showMemo = false;
			showMemoDetail = false;
		}

		return;
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

	if (!showMemo) {
		switch (player.currentRoom)
		{
		case ROOM_FIRST:
			if (player.bookshelfMenu)
			{
				chemistryBookButton.DrawArea();
				pictureBookButton.DrawArea();
				closeBookshelfButton.DrawArea();
				
				chemistryBookButton.DrawLabel("化学の本");
				pictureBookButton.DrawLabel("絵本");
				closeBookshelfButton.DrawLabel("本棚から離れる");
			}
			else {
				bedButton.DrawArea();
				deskButton.DrawArea();
				bookshelfButton.DrawArea();
				doorButton.DrawArea();

				bedButton.DrawLabel("ベッド");
				deskButton.DrawLabel("机");
				bookshelfButton.DrawLabel("本棚");
				doorButton.DrawLabel("扉");
			}

			break;

		case ROOM_HALL:

			labDoorButton.DrawArea();
			storageDoorButton.DrawArea();
			noteButton.DrawArea();

			labDoorButton.DrawLabel("研究室");
			storageDoorButton.DrawLabel("倉庫");
			noteButton.DrawLabel("張り紙のある部屋");

			break;
		case ROOM_LAB:
			fairyBookButton.DrawArea();
			fairyBookButton.DrawLabel("絵本");
			maskButton.DrawArea();
			maskButton.DrawLabel("防毒マスク");
			hoseButton.DrawArea();
			hoseButton.DrawLabel("ホース");
			backHallFromLabButton.DrawArea();
			backHallFromLabButton.DrawLabel("廊下へ戻る");

			break;

		case ROOM_STORAGE:


			diaryButton.DrawArea();
			diaryButton.DrawLabel("古い日記");
			pamButton.DrawArea();
			pamButton.DrawLabel("PAM注射");
			fireDocButton.DrawArea();
			fireDocButton.DrawLabel("消火資料");
			backHallFromStorageButton.DrawArea();
			backHallFromStorageButton.DrawLabel("廊下へ戻る");

			break;
		}
	}

	if (showMemo)
	{
		DrawMemo();
	}
}