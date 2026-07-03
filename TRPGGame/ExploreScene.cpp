#include "ExploreScene.h"
#include "DxLib.h"
#include "SaveData.h"
#include "UIButton.h"
#include < stdlib.h >
#include "SceneManager.h"
#include "Pause.h"
#include "DiceSystem.h"
#include "BGM.h"

/// 寝室
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
/// 廊下
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
/// 研究所
// 記録
Button NoteBookButton(
	500, 650,
	260, 180);
// 机
Button labDeskButton(
	340, 540,
	450, 200);
// 絵本
Button matchBookButton(
	260, 550,
	260, 180);
// 戻る
Button DeskbackButton(
	750, 500,
	400, 200);

// 右棚の防毒マスク
Button labShelfButton(
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
// メモを閉じるボタン
Button memoBackButton(
	1250, 820,
	180, 60);
// メモ表示ボタン一覧
Button memoDoc1Button(
	320, 300,
	500, 30);

Button memoDoc2Button(
	320, 340,
	500, 30);

Button memoDoc3Button(
	320, 380,
	500, 30);

Button memoBookButton(
	320, 420,
	500, 30);

Button memoObserveNoteButton(
	320, 460,
	500, 30);

Button memoCopyPaperButton(
	320, 500,
	500, 30);

Button memoLetterButton(
	320, 540,
	500, 30);

Button memoFireDocButton(
	320, 580,
	500, 30);

// ルームの名前表示用
const char* roomName[] =
{
	"寝室",
	"廊下",
	"研究室",
	"倉庫"
};

// 状態
int roomBG[4];
bool IsShowMemo = false;		// メモ表示フラグ

char message[2048] = "";		// メッセージ表示用
int memoSelect = 0;				// 選択中のメモ
bool IsShowMemoDetail = false;	// メモ詳細表示フラグ

int LastDice = 0;					// 直前のダイス結果
bool IsShowDice = false;			// サイコロ表示フラグ
bool IsFirstRoomExitReady = false;	// 初期部屋脱出フラグ

int DiceImage[6];		// サイコロ画像
int faceTimer = 0;		// 表情表示タイマー

PlayerFace playerFace;	// プレイヤー表情

// プレイヤー画像
int PlayerNormalImage;
int PlayerThinkImage;
int PlayerDamageImage;

Memo memo[50];			// メモデータ

MemoType currentMemo = MEMO_NONE;	// 現在表示中のメモ
// ダイスを振る
int RollDice(int max)
{
	return rand() % max + 1;
}
// 必要な探索が完了しているか判定する
bool IsAllExploreFinished()
{
	return
		player.checkedBed &&
		player.checkedDesk &&
		player.checkedBookshelf &&
		player.labcheckeddeskall &&
		player.hasMask &&
		player.checkedSink &&
		player.checkedDiary &&
		player.hasPAM &&
		player.checkedFireDoc;
}
// 能力値判定を行う
bool SkillCheck(int skill)
{
	LastDice = RollDice(6);
	IsShowDice = true;

	return LastDice <= skill;
}
// プレイヤーにダメージを与える
void DamagePlayer(int damage)
{
	player.hp -= damage;

	if (player.hp < 0)
	{
		player.hp = 0;
	}
}
// 部屋移動を行う
void ChangeRoom(RoomType room, const char* text)
{
	int damage = RollDice(2);

	DamagePlayer(damage);

	PlaySoundMem(
		sePoison,
		DX_PLAYTYPE_BACK);

	playerFace = FACE_DAMAGE;

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
// 探索シーンを初期化する
void InitExploreScene()
{
	player.currentRoom = ROOM_FIRST;

	strcpy_s(message,
		"目が覚めた。\n"
		"妙に息が苦しいような気がする....\n"
		"探索をしに行こう。");

	roomBG[ROOM_FIRST] = LoadGraph("Image\\firstroom.png");
	roomBG[ROOM_HALL] = LoadGraph("Image\\hall.png");
	roomBG[ROOM_LAB] = LoadGraph("Image\\lab.png");
	roomBG[ROOM_STORAGE] = LoadGraph("Image\\storage.png");

	DiceImage[0] = LoadGraph("Image\\Dice1.png");
	DiceImage[1] = LoadGraph("Image\\Dice2.png");
	DiceImage[2] = LoadGraph("Image\\Dice3.png");
	DiceImage[3] = LoadGraph("Image\\Dice4.png");
	DiceImage[4] = LoadGraph("Image\\Dice5.png");
	DiceImage[5] = LoadGraph("Image\\Dice6.png");


	PlayerNormalImage =
		LoadGraph("Image\\main.png");

	PlayerThinkImage =
		LoadGraph("Image\\main2.png");

	PlayerDamageImage =
		LoadGraph("Image\\main3.png");

}
// プレイヤーを描画する
void DrawPlayer() {

	DrawBox(
		170, 10,
		320, 160,
		GetColor(0, 0, 0),
		TRUE);

	DrawBox(
		170, 10,
		320, 160,
		GetColor(255, 255, 255),
		FALSE);


	if (faceTimer == 0 && playerFace != FACE_NORMAL) {
		faceTimer = 180;
	}

	switch (playerFace)
	{
	case FACE_NORMAL:

		DrawExtendGraph(
			180, 20,
			310, 150,
			PlayerNormalImage,
			TRUE);

		break;

	case FACE_THINK:

		DrawExtendGraph(
			180, 20,
			310, 150,
			PlayerThinkImage,
			TRUE);

		break;

	case FACE_DAMAGE:

		DrawExtendGraph(
			180, 20,
			310, 150,
			PlayerDamageImage,
			TRUE);

		break;
	}
}
// プレイヤー表情を更新する
void UpdatePlayerFace()
{
	if (faceTimer > 0)
	{
		faceTimer--;

		if (faceTimer <= 0)
		{
			playerFace = FACE_NORMAL;
		}
	}
}
// 寝室の処理
void Update_FirstRoom()
{
	
	if (!player.bookshelfMenu) {
		// ベッド
		if (bedButton.IsClicked())
		{
			if (!player.checkedBed)
			{
				player.checkedBed = true;

				bool success = SkillCheck(player.insight);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

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

					playerFace = FACE_THINK;
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
					playerFace = FACE_NORMAL;
				}
			}
			else
			{
				strcpy_s(message,
					"もうここは調べても意味がないだろう。");
				playerFace = FACE_NORMAL;
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
				playerFace = FACE_THINK;
				player.checkedDesk = true;
			}
			else
			{
				playerFace = FACE_THINK;


				if (player.deskSearchCount == 3 &&
					!player.foundLeftMemo)
				{
					bool success = SkillCheck(player.insight);

					IsPendingSuccess = success;

					StartDiceAnimation(LastDice);

					if (success)
					{

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
					player.foundLeftMemo = true;
					return;
				}

				if (player.deskSearchCount >= 3)
				{
					playerFace = FACE_NORMAL;

					strcpy_s(message,
						"もう十分調べた。");
					return;
				}

				player.deskSearchCount++;

				bool success = SkillCheck(player.knw);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

				if (!success)
				{
					char temp[256];

					int n = 3 - player.deskSearchCount;

					if (n < 0) {
						n = 0;
						sprintf_s(temp,
							"知識判定\n"
							"D6 → %d\n\n"
							"失敗...\n"
							"有用な資料は見つからなかった。\n"
							"まだ何かあるようだ。調べてみよう \n\n"
							"残り調査回数:%d",
							LastDice,
							n);

					}
					else {
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

	}

	if (bookshelfButton.IsClicked())
	{
		playerFace = FACE_THINK;

		if (!player.checkedBookshelf)
		{
			player.checkedBookshelf = true;
			
			bool success = SkillCheck(player.knw);

			IsPendingSuccess = success;

			StartDiceAnimation(LastDice);

			if (success)
			{
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
					"他の本を確認してみよう。", LastDice);
			}
		}
		else {

			playerFace = FACE_NORMAL;
			strcpy_s(message,
				"本棚をまた確認しよう。");
		}

		player.bookshelfMenu = true;
	}

	if (player.bookshelfMenu)
	{
		if (chemistryBookButton.IsClicked())
		{
			playerFace = FACE_THINK;

			if (!player.checkedChemBook)
			{
				player.checkedChemBook = true;

				bool success = SkillCheck(player.knw);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

				if (success)
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

				playerFace = FACE_NORMAL;
				strcpy_s(message,
					"先ほど読んだ本だ。");
			}
		}


		if (pictureBookButton.IsClicked())
		{
			playerFace = FACE_THINK;

			if (!player.checkedPictureBook)
			{
				player.checkedPictureBook = true;

				bool success = SkillCheck(player.insight);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

				if (success)
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

				bool success = SkillCheck(player.insight);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

				if (success)
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
			playerFace = FACE_NORMAL;
			strcpy_s(message,
				"もう見るところはないはずだろう。");
		}

		return;
	}

	if (doorButton.IsClicked())
	{
		if (!IsFirstRoomExitReady)
		{
			IsFirstRoomExitReady = true;
			playerFace = FACE_THINK;
			strcpy_s(message,
				"一度他の部屋の探索をする必要がありそうだ...");
		}
		else
		{
			IsFirstRoomExitReady = false;
			ChangeRoom(
				ROOM_HALL,
				message);
		}
	}
}
// 廊下の処理
void Update_Hall()
{
	if (labDoorButton.IsClicked())
	{
		ChangeRoom(
			ROOM_LAB,
			"広い机とキャスター付きの丸椅子がある。\n"
			"右手には簡易棚。\n"
			"奥には大きなシンクが設置されている。\n\n"
			"研究室のようだ。");
	}

	if (storageDoorButton.IsClicked())
	{
		ChangeRoom(
			ROOM_STORAGE,
			"倉庫のようだ。\n"
			"いろいろな物が置いてある。"
			);
	}

	if (noteButton.IsClicked())
	{
		playerFace = FACE_THINK;

		// 初回
		if (!player.bossDoorReady)
		{
			player.bossDoorReady = true;

			strcpy_s(message,
				"『必ずマスクを着用』と書かれている。\n"
				"異様な雰囲気を漂わせている。\n"
				"入口付近に消火器が置かれている。\n\n"
				"もしかすると扉をこじ開けられそうだ...");
		}

		// 開放済み
		else if (player.canEnterBossRoom)
		{
			currentScene = SCENE_GAMEFIGHT;

			StartFinalBattle();

			static bool n = false;

			if (!player.hasMask && !n) {

				finalIntroState = FINAL_BATTLE;

				finalBattleState = END3;

				n = true;
			}

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

			IsPendingSuccess = success;

			StartDiceAnimation(LastDice);

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
// 研究室の処理
void Update_Lab()
{
	if (player.labDeskMenu)
	{
		if (matchBookButton.IsClicked())
		{

			playerFace = FACE_THINK;
			player.checkedMatchBook = true;

			if (!player.foundBurnMark)
			{
				bool success = SkillCheck(player.insight);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

				if (success)
				{
					player.foundBurnMark = true;

					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"『マッチ売りの少女』だ。\n"
						"何度も読まれた形跡がある。\n\n"
						"汚れの一部は焦げ跡のようだ。",
						LastDice);

					player.checkedMatchBook = true;
				}
				else
				{
					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"失敗...\n"
						"何かの絵本だ。\n"
						"何度も読まれた形跡がある。",
						LastDice);
				}
			}
			else
			{

				playerFace = FACE_NORMAL;
				strcpy_s(message,
					"もう確認した。");
			}
		}

		if (NoteBookButton.IsClicked())
		{
			playerFace = FACE_THINK;

			if (!player.readObserveDetail)
			{
				player.readObserveDetail = true;

				bool success = SkillCheck(player.insight);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

				if (success)
				{
					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"観察記録だ。\n\n"
						"対象『15』は水を浴びせると\n"
						"鎮静化するらしい。\n\n",
						LastDice);

					player.checkedNotebook = true;
				}
				else
				{
					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"失敗...\n"
						"観察記録だ。",
						LastDice);
				}
			}
			else
			{

				playerFace = FACE_NORMAL;
				strcpy_s(message,
					"観察記録だ。");
			}
		}

		if (DeskbackButton.IsClicked())
		{

			playerFace = FACE_NORMAL;
			player.labDeskMenu = false;

			strcpy_s(message,
				"机から離れた。");
		}
	}
	else {

		if (labDeskButton.IsClicked())
		{
			playerFace = FACE_THINK;

			strcpy_s(message,
				"雑然とした机だ。\n"
				"絵本とノートが置かれている。\n"
				"\n"
				"調べてみよう。");

			player.labDeskMenu = true;
			player.labcheckeddeskall = true;
		}

		// 防毒マスク
		if (labShelfButton.IsClicked())
		{
			playerFace = FACE_THINK;

			if (!player.checkedShelf)
			{
				player.checkedShelf = true;

				if (!player.hasMask)
				{
					player.hasMask = true;
				}


				bool success = SkillCheck(player.insight);

				IsPendingSuccess = success;

				StartDiceAnimation(LastDice);

				if (success)
				{
					player.checkedCopyPaper = true;

					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"成功！\n"
						"防毒マスクを発見した。\n\n"
						"コピー用紙の束に紛れて\n"
						"文字の書かれた紙を見つけた。\n",
						LastDice);
				}
				else
				{
					sprintf_s(message,
						"洞察判定\n"
						"D6 → %d\n\n"
						"失敗...\n"
						"防毒マスクを発見した。",
						LastDice);
				}
			}
			else
			{
				playerFace = FACE_NORMAL;

				strcpy_s(message,
					"もう十分調べた。");
			}
		}

		// ホース
		if (hoseButton.IsClicked())
		{
			playerFace = FACE_THINK;

			if (player.checkedSink)
			{

				playerFace = FACE_NORMAL;
				strcpy_s(message,
					"もう確認した。");
			}
			else
			{
				player.checkedSink = true;

				strcpy_s(message,
					"ステンレスのシンク。蛇口をひねれば水が出る。\n"
					"近くには、長いホースがとぐろを巻いた状態で落ちている。");
			}
		}

		// 廊下へ戻る
		if (backHallFromLabButton.IsClicked())
		{
			strcpy_s(message,
				"廊下に戻ろう。\n\n");

			ChangeRoom(
				ROOM_HALL,
				message);
		}
	}
}
// 倉庫の処理
void Update_Storage()
{
	if (diaryButton.IsClicked())
	{
		playerFace = FACE_THINK;

		if (!player.checkedDiary)
		{
			player.checkedDiary = true;

			int damage = RollDice(2);

			player.hp -= damage;

			if (player.hp < 0)
			{
				player.hp = 0;
			}

			bool success = SkillCheck(player.insight);

			IsPendingSuccess = success;

			StartDiceAnimation(LastDice);

			if (success)
			{
				player.foundLetter = true;

				sprintf_s(message,
					"洞察判定\n"
					"D6 → %d\n"
					"成功！\n"
					"古い日記\n"
					"島で行われた儀式の日、\n"
					"発光する異形の存在が現れた。"
					"島民はリン中毒で死亡。\n"
					"生存者は教師と加古のみ。"
					"加古は異形の子を出産し死亡。\n"
					"教師はその子を『15』と名付けた。\n"
					"ショッキングな内容だ...\n"
					"HP-%d",
					damage,
					LastDice);
			}
			else
			{
				sprintf_s(message,
					"洞察判定\n"
					"D6 → %d\n"
					"失敗...\n"
					"あまり資料は見つからなかった。",
					LastDice);
			}
		}
		else
		{
			playerFace = FACE_NORMAL;

			strcpy_s(message,
				"もう十分調べた。");
		}
	}

	if (pamButton.IsClicked())
	{
		playerFace = FACE_THINK;

		if (!player.hasPAM)
		{
			player.hasPAM = true;

			bool success = SkillCheck(player.insight);

			IsPendingSuccess = success;

			StartDiceAnimation(LastDice);

			if (success)
			{
				player.hp += 3;

				sprintf_s(message,
					"洞察判定\n"
					"D6 → %d\n\n"
					"成功！\n"
					"『PAM』と書かれたケースを発見した。\n"
					"注射器も置かれている。\n"
					"使用し、HPが 3 回復した！",
					LastDice);
			}
			else
			{
				sprintf_s(message,
					"洞察判定\n"
					"D6 → %d\n\n"
					"失敗...\n"
					"何かの薬のようなものがたくさん置かれている\n"
					"なんの薬かはわからない。",
					LastDice);
			}
		}
		else
		{
			playerFace = FACE_NORMAL;

			strcpy_s(message,
				"もう確認した。");
		}
	}

	if (fireDocButton.IsClicked())
	{
		playerFace = FACE_THINK;

		if (!player.checkedFireDoc)
		{
			player.checkedFireDoc = true;

			bool success = SkillCheck(player.insight);

			IsPendingSuccess = success;

			StartDiceAnimation(LastDice);

			if (success)
			{
				player.readFireDoc = true;
				sprintf_s(message,
					"知識判定\n"
					"D6 → %d\n\n"
					"成功！\n\n"
					"『消火について』という資料だ。\n\n"
					"危険物火災の項目には\n"
					"リンによる火災についての\n"
					"記述がある。",
					LastDice);
			}
			else
			{
				sprintf_s(message,
					"知識判定\n"
					"D6 → %d\n\n"
					"失敗...\n\n"
					"消火に関する資料だが\n"
					"必要な情報は見つからなかった。",
					LastDice);
			}
		}
		else
		{
			playerFace = FACE_NORMAL;

			strcpy_s(message,
				"『消火について』という資料だ。");
		}
	}
	
	// 廊下へ戻る
	if (backHallFromStorageButton.IsClicked())
	{
		strcpy_s(message,
			"廊下に戻ろう。\n\n");

		ChangeRoom(
			ROOM_HALL,
			message);
	}
}
// メモ機能を更新する
void UpdateMemo()
{
	if (!IsShowMemo)
	{
		return;
	}

	if (IsShowMemoDetail)
	{
		if (memoBackButton.IsClicked())
		{
			IsShowMemoDetail = false;
			currentMemo = MEMO_NONE;
		}

		return;
	}

	if (player.readDoc1 &&
		memoDoc1Button.IsClicked())
	{
		currentMemo = MEMO_DOC1;
		IsShowMemoDetail = true;
	}

	if (player.readDoc2 &&
		memoDoc2Button.IsClicked())
	{
		currentMemo = MEMO_DOC2;
		IsShowMemoDetail = true;
	}

	if (player.readDoc3 &&
		memoDoc3Button.IsClicked())
	{
		currentMemo = MEMO_DOC3;
		IsShowMemoDetail = true;
	}

	if (player.checkedMatchBook &&
		memoBookButton.IsClicked())
	{
		currentMemo = MEMO_FAIRYBOOK;
		IsShowMemoDetail = true;
	}

	if (player.checkedNotebook &&
		memoObserveNoteButton.IsClicked())
	{
		currentMemo = MEMO_OBSERVE_NOTE;
		IsShowMemoDetail = true;
	}

	if (player.checkedCopyPaper &&
		memoCopyPaperButton.IsClicked()) {
		currentMemo = MEMO_COPY_PAPER;
		IsShowMemoDetail = true;
	}

	if (player.foundLetter &&
		memoLetterButton.IsClicked()) {
		currentMemo = MEMO_DIARY;
		IsShowMemoDetail = true;
	}

	if (player.readFireDoc &&
		memoFireDocButton.IsClicked()) {
		currentMemo = MEMO_FIREDOC;
		IsShowMemoDetail = true;
	}
}
// 探索シーン全体を更新する
void UpdateExploreScene()
{

	UpdatePlayerFace();

	if (IsKeyPressedOnce(KEY_INPUT_TAB))
	{
		IsShowMemo = !IsShowMemo;
	}

	if (IsShowMemo || isPause)
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

	UpdateDiceUI();

	if (player.hp <= 0)
	{
		currentScene = SCENE_GAMEFIGHT;

		StartFinalBattle();

		static bool n = false;

		if (!player.hasMask && !n) {

			finalIntroState = FINAL_BATTLE;

			finalBattleState = END3;

			n = true;
		}
	}
}
// メッセージ欄を描画する
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
// ステータスを描画する
void DrawStatus()
{
	DrawFormatString(
		60,
		60,
		GetColor(255, 255, 255),
		"HP : %d",
		player.hp);
}
// 部屋名を描画する
void DrawRoomName()
{
	DrawString(
		60,
		20,
		roomName[player.currentRoom],
		GetColor(255, 255, 255));
}
// メモ内容を描画する
void DrawMemoDetail()
{
	DrawBox(
		400, 150,
		1520, 930,
		GetColor(10, 10, 10),
		TRUE);

	DrawBox(
		400, 150,
		1520, 930,
		GetColor(255, 255, 255),
		FALSE);

	switch (currentMemo)
	{
	case MEMO_DOC1:

		DrawString(
			450,
			220,
			"リンは『賢者の石』と呼ばれていた。\n\n"
			"錬金術師ヘンニヒ・ブラントは、\n"
			"金を生み出す研究の最中に\n"
			"リンを発見した。\n\n"
			"暗闇で青白く光る性質から、\n"
			"彼はこれを『賢者の石』だと\n"
			"考えたという。\n\n"
			"この光は腐敗した生物からも\n"
			"発生することがあり、\n"
			"人魂の正体とも言われている。",
			GetColor(255, 255, 255));

		break;

	case MEMO_DOC2:

		DrawString(
			450,
			220,
			"世界各地で『燃える石』と\n"
			"呼ばれる現象が報告されている。\n\n"
			"その多くは白リンや黄リンが\n"
			"原因とされている。\n\n"
			"これらは30〜60℃程度で\n"
			"発火するため、暑い日には\n"
			"自然発火する危険がある。\n\n"
			"そのため通常は空気に触れない\n"
			"よう、水中で保管される。",
			GetColor(255, 255, 255));

		break;

	case MEMO_DOC3:

		DrawString(
			450,
			220,
			"現在のマッチには赤リンが\n"
			"使われている。\n\n"
			"しかし昔は黄リンが原料として\n"
			"使用されていた。\n\n"
			"黄リンは猛毒であり、\n"
			"工場労働者の健康被害が\n"
			"社会問題となった。\n\n"
			"童話『マッチ売りの少女』で\n"
			"描かれた幻覚も、黄リンの\n"
			"影響だった可能性があるという。\n\n"
			"黄リンは独特なニンニク臭を\n"
			"放つことで知られている。",
			GetColor(255, 255, 255));

		break;

	case MEMO_FAIRYBOOK:

		DrawString(
			450,
			180,
			"【マッチ売りの少女】\n\n"
			"寒い冬の日、少女は街でマッチを売っていた。\n"
			"しかし誰も買ってくれなかった。\n\n"
			"少女は寒さに耐えられずマッチを擦る。\n"
			"すると暖かなストーブが現れた。\n"
			"しかし火が消えるとストーブも消えた。\n\n"
			"次にマッチを擦ると豪華なごちそうが現れた。\n"
			"しかしそれも消えてしまった。\n\n"
			"さらにクリスマスツリーが現れたが、\n"
			"やがて消えてしまった。\n\n"
			"最後に亡くなった祖母が現れ、\n"
			"少女を優しく抱きしめた。\n\n"
			"翌朝、少女は微笑みながら\n"
			"凍死しているのが発見された。",
			GetColor(255, 255, 255));

		break;

	case MEMO_OBSERVE_NOTE:

		DrawString(
			450,
			220,
			"【観察記録1】\n\n"
			"対象『15』は毒性の蒸気を放つ。\n"
			"接触には防毒マスクが必須。\n\n"
			"身体能力は日々成長しており、\n"
			"高温のリンを含む体液を\n"
			"撒き散らすようになった。\n\n"
			"精神が不安定になると暴走するが、\n"
			"水を浴びせることで\n"
			"鎮静化できるらしい。\n\n"
			"『マッチ売りの少女』を\n"
			"異常なほど気に入っている。\n\n"
			"研究者の名前は\n"
			"『左部』のようだ。",
			GetColor(255, 255, 255));

		break;
	case MEMO_COPY_PAPER:

		DrawString(
			450,
			220,
			"【コピー用紙】\n\n"
			"誰もいない、なにもない島だ。\n"
			"こんな島に誰が戻る。\n\n"
			"15は水の中では活動できない。\n"
			"本土へ向かうことはありえない。\n\n"
			"被害がでることもないだろう。",
			GetColor(255, 255, 255));

		break;

	case MEMO_DIARY:

		DrawString(
			450,
			220,
			"【古い日記】\n\n"
			"過疎化により島の住民は減少し、\n"
			"最後の生徒も島を去った。\n\n"
			"その後の儀式の日、天から光が降り、\n"
			"発光する異形の存在が現れた。\n\n"
			"強いニンニク臭と共に島民は倒れ、\n"
			"多くがリン中毒で死亡した。\n\n"
			"生き残ったのは教師と加古のみ。\n"
			"加古は異形の子を身籠り、\n"
			"出産後に死亡した。\n\n"
			"産まれた子は人間に似ていたが、\n"
			"身体が流動し続ける異形だった。\n\n"
			"教師はその存在を研究し、\n"
			"リンにちなみ『15』と名付けた。",
			GetColor(255, 255, 255));

		break;

	case MEMO_FIREDOC:
		DrawString(
			450,
			220,
			"【消火資料】\n\n"
			"火災は原因によって\n"
			"消火方法が異なる。\n\n"
			"危険物火災の場合、\n"
			"水と反応する物質かを\n"
			"確認する必要がある。\n\n"
			"リンによる火災は\n"
			"水や消火剤で消火可能。\n\n"
			"ただし棒状ではなく\n"
			"霧状に散布すること。\n\n"
			"危険物が飛散すると\n"
			"被害が拡大する。",
			GetColor(255, 255, 255));

		break;
	}

	memoBackButton.Draw(false);
	memoBackButton.DrawLabel("戻る");
}
// メモ一覧を描画する
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

	if (player.readDoc1)
	{
		DrawString(
			320,
			300,
			"・リンは『賢者の石』",
			GetColor(255, 255, 255));
	}

	if (player.readDoc2)
	{
		DrawString(
			320,
			340,
			"・燃える石",
			GetColor(255, 255, 255));
	}

	if (player.readDoc3)
	{
		DrawString(
			320,
			380,
			"・マッチ売りの少女",
			GetColor(255, 255, 255));
	}

	if (player.checkedMatchBook)
	{
		DrawString(
			320,
			420,
			"・マッチ売りの少女「原文」",
			GetColor(255, 255, 255));
	}

	if (player.checkedNotebook)
	{
		DrawString(
			320,
			460,
			"・観察記録1",
			GetColor(255, 255, 255));
	}

	if (player.checkedCopyPaper)
	{
		DrawString(
			320,
			500,
			"・コピー用紙",
			GetColor(255, 255, 255));
	}

	if (player.foundLetter)
	{
		DrawString(
			320,
			540,
			"・古い日記",
			GetColor(255, 255, 255));
	}

	if (player.readFireDoc)
	{
		DrawString(
			320,
			580,
			"・消化について",
			GetColor(255, 255, 255));
	}
}
// 探索画面を描画する
void DrawExploreScene()
{
	DrawExtendGraph(
		0,
		0,
		1920,
		1080,
		roomBG[player.currentRoom],
		TRUE);

	DrawPlayer();

	DrawRoomName();

	DrawStatus();

	DrawMessageBox();

	if (!IsShowMemo && !isPause) {
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
			if (player.labDeskMenu) {
				NoteBookButton.DrawArea();
				matchBookButton.DrawArea();
				DeskbackButton.DrawArea();

				NoteBookButton.DrawLabel("とある観察記録");
				matchBookButton.DrawLabel("絵本");
				DeskbackButton.DrawLabel("戻る");

			}
			else {

				labDeskButton.DrawArea();
				labDeskButton.DrawLabel("机");
				labShelfButton.DrawArea();
				labShelfButton.DrawLabel("棚");
				hoseButton.DrawArea();
				hoseButton.DrawLabel("シンク");
				backHallFromLabButton.DrawArea();
				backHallFromLabButton.DrawLabel("廊下へ戻る");
			}

			break;

		case ROOM_STORAGE:

			diaryButton.DrawArea();
			diaryButton.DrawLabel("左の棚");
			pamButton.DrawArea();
			pamButton.DrawLabel("右の棚");
			fireDocButton.DrawArea();
			fireDocButton.DrawLabel("真ん中の棚");
			backHallFromStorageButton.DrawArea();
			backHallFromStorageButton.DrawLabel("廊下へ戻る");

			break;
		}
	}

	DrawDiceUI();

	if (IsShowMemo && !isPause)
	{
		DrawMemo();
		UpdateMemo();
		if (IsShowMemoDetail)
		{
			DrawMemoDetail();
		}
	}
}