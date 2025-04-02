// 1. В една софтуерна компания се провежда турнир по белот с благотворителна цел.

// * Трябва да създадете клас BelotTournament, който да провежда турнира. За да бъде проведен един турнир, трябва да има отбори от софтуерни инженери. Всеки отбор се състои от 2 софтуерни инженери. Всеки софтуерен инженер има име (низ с произволна дължина), позиция (низ с произволна дължина) и заплата (цяло число).

// Броят на отборите трябва да е четен и по-голям от 2. При опит да започне турнира с нечетен брой отбори, последният добавен отбор бива премахнат преди началото на турнира.

// Когато имато достатъчно отбори, чиито участници са валидни, тогава турнирът може да започне. Отборите биват разпределени на случаен принцип. След това се провежда дуел между отборите. Един дуел може да има максимално 3 рунда, като първият отбор достигнал 2 победи, печели дуела. Един рунд се провежда като за всеки отбор се четат точки от конзолата, които се добавя към общите точки на отбора. Рунда печели отборът, който първи достигне число 151. Това се повтаря за всички печеливши отбори, докато не остане един единствен отбор, който е победител. Тъй като турнирът е с благотворителна цел, всеки от загубилите участници дарява 2% от заплатата си, а 1% дават на всеки от печелившия отбор. Да се пресметне колко пари е събрала фирмата от турнира за дарение.

#include <iostream>
#include <cstdlib>

class BelotTournament
{
public:
  BelotTournament() : teamsCount(0), totalDonations(0) {}

  void addTeam()
  {
    if (teamsCount >= MAX_TEAMS)
    {
      std::cout << "Tournament is full. Cannot add more teams.\n";
      return;
    }

    Team &team = teams[teamsCount];
    team.teamId = teamsCount + 1;

    for (int i = 0; i < 2; i++)
    {
      std::cout << "Enter name for engineer " << i + 1 << ": ";
      std::cin.ignore();
      std::cin.getline(team.engineers[i].name, 128);

      std::cout << "Enter position for engineer " << i + 1 << ": ";
      std::cin.getline(team.engineers[i].position, 128);

      std::cout << "Enter salary for engineer " << i + 1 << ": ";
      std::cin >> team.engineers[i].salary;
    }

    teamsCount++;
    std::cout << "Team " << team.teamId << " added successfully!\n";
  }

  void startTournament()
  {
    if (teamsCount % 2 != 0)
    {
      std::cout << "Odd number of teams. Removing last team.\n";
      teamsCount--;
    }

    while (teamsCount > 1)
    {
      int newTeamsCount = 0;
      for (unsigned i = 0; i < teamsCount; i += 2)
      {
        int winner = playDuel(i, i + 1);
        teams[newTeamsCount++] = teams[winner];
      }
      teamsCount = newTeamsCount;
    }

    std::cout << "Tournament winner: Team " << teams[0].teamId << "!\n";
    printTeam(teams[0]);
    std::cout << "Total amount donated: " << totalDonations << " BGN\n";
  }

private:
  struct Engineer
  {
    char name[128];
    char position[128];
    unsigned salary;
  };

  struct Team
  {
    int teamId;
    Engineer engineers[2];
  };

  static const unsigned MAX_TEAMS = 10;
  Team teams[MAX_TEAMS];
  unsigned teamsCount;
  double totalDonations;

  int playDuel(int index1, int index2)
  {
    std::cout << "Team " << teams[index1].teamId << " vs Team " << teams[index2].teamId << "\n";

    int wins1 = 0, wins2 = 0;
    for (int i = 0; i < 3; i++)
    {
      int points1 = 0, points2 = 0, input;

      std::cout << "Round " << i + 1 << std::endl;

      while (points1 < 151 && points2 < 151)
      {
        std::cout << "Enter points for Team " << teams[index1].teamId << ": ";
        std::cin >> input;
        points1 += input;

        std::cout << "Enter points for Team " << teams[index2].teamId << ": ";
        std::cin >> input;
        points2 += input;
      }

      if (points1 >= 151)
        wins1++;
      else
        wins2++;

      if (wins1 == 2 || wins2 == 2)
        break;
    }

    int winner = (wins1 > wins2) ? index1 : index2;
    int loser = (winner == index1) ? index2 : index1;

    for (int i = 0; i < 2; i++)
    {
      totalDonations += teams[loser].engineers[i].salary * 0.02;
      totalDonations += teams[winner].engineers[i].salary * 0.01;
    }

    std::cout << "Duel winner: Team " << teams[winner].teamId << "\n";
    printTeam(teams[winner]);
    return winner;
  }

  void printTeam(const Team &team)
  {
    std::cout << "Team " << team.teamId << " members:\n";
    for (int i = 0; i < 2; i++)
    {
      std::cout << "  Name: " << team.engineers[i].name
                << ", Position: " << team.engineers[i].position
                << ", Salary: " << team.engineers[i].salary << " BGN\n";
    }
  }
};

int main()
{
  BelotTournament tournament;
  int numTeams;

  std::cout << "Enter number of teams: ";
  std::cin >> numTeams;

  for (int i = 0; i < numTeams; i++)
  {
    std::cout << "\nAdding team " << i + 1 << ":\n";
    tournament.addTeam();
  }

  tournament.startTournament();
  return 0;
}
