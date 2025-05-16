#include <exception>
#include <iostream>
#include <ostream>

struct Position
{
  int x;
  int y;
};

Position operator-(const Position &a, const Position &b)
{
  return Position{a.x - b.x, a.y - b.y};
}

bool operator==(const Position &a, const Position &b)
{
  return a.x == b.x && a.y == b.y;
}

bool operator!=(const Position &a, const Position &b)
{
  return !(a == b);
}

Position abs(const Position &a)
{
  return Position{abs(a.x), abs(a.y)};
}

std::ostream &operator<<(std::ostream &out, const Position &p)
{
  return out << p.x << ' ' << p.y;
}

enum class PlayerType
{
  Player,
  Mage,
  Warrior,
  Necromancer
};

class Player
{
public:
  friend std::ostream &operator<<(std::ostream &out, const Player &p);
  enum Weapon
  {
    Sword,
    Wand,
    Staff,
    Axe
  };

protected:
  PlayerType type;
  char *name = nullptr;
  unsigned health;
  Position position;
  Weapon weapon;
  unsigned attack_damage;

  void setName(const char *name)
  {
    if (!name)
    {
      throw std::logic_error("Empty Player name");
    }
    char *newName = new char[strlen(name) + 1];
    strcpy(newName, name);

    delete[] this->name;
    this->name = newName;
  }

  void swap(Player &other)
  {
    std::swap(type, other.type);
    std::swap(name, other.name);
    std::swap(health, other.health);
    std::swap(position, other.position);
    std::swap(weapon, other.weapon);
    std::swap(attack_damage, other.attack_damage);
  }

public:
  Player(PlayerType type, const char *name, unsigned health, const Position &pos, Weapon weapon, unsigned damage)
      : type(type), health(health), position(pos), weapon(weapon), attack_damage(damage)
  {
    setName(name);
  }

  Player(const Player &other)
      : type(other.type), health(other.health), position(other.position), weapon(other.weapon), attack_damage(other.attack_damage)
  {
    setName(other.name);
  }

  void move(const Position &pos)
  {
    position = pos;
  }

  bool isDead() const
  {
    return health == 0;
  }

  const Position &getPosition() const
  {
    return position;
  }

  const char *getName() const
  {
    return name;
  }

  PlayerType getType() const
  {
    return type;
  }

  void handleAttack(Player &other);

  unsigned getAttackPower() const
  {
    return attack_damage;
  }

  Player &operator=(const Player &other)
  {
    if (this == &other)
      return *this;
    type = other.type;
    setName(other.name);
    health = other.health;
    position = other.position;
    weapon = other.weapon;
    attack_damage = other.attack_damage;
    return *this;
  }

  virtual ~Player()
  {
    delete[] name;
  }

  void print()
  {
    std::cout << *this;
  }

  virtual Player *clone() const = 0;

  void freeMem();
};

std::ostream &operator<<(std::ostream &out, const Player &p)
{
  return out << p.health << ' ' << p.name << ' ' << p.attack_damage << ' ' << p.position;
}

class Warrior : public Player
{
  unsigned armor;

public:
  Warrior(const char *name, unsigned health, const Position &pos, Weapon weapon, unsigned damage, unsigned armor)
      : Player(PlayerType::Warrior, name, health, pos, weapon, damage), armor(armor)
  {
  }

  void handleAttack(Player &other);

  Player *clone() const override
  {
    return new Warrior(*this);
  }
};

class Mage : public Player
{
  char *ability = nullptr;
  float attackMultiplier;

  void swap(Mage &other)
  {
    std::swap(ability, other.ability);
    std::swap(attackMultiplier, other.attackMultiplier);
    Player::swap(other);
  }

public:
  Mage(const char *name, unsigned health, const Position &pos, Weapon weapon, unsigned damage, const char *ability, float multiplier)
      : Player(PlayerType::Mage, name, health, pos, weapon, damage), attackMultiplier(multiplier)
  {
    if (multiplier >= 1 || multiplier <= 0)
    {
      throw std::logic_error("Mage multiplier must be in (0, 1)");
    }
    setAbility(ability);
  }

  ~Mage()
  {
    delete[] ability;
  }

  Mage(const Mage &other)
      : Player(other), attackMultiplier(other.attackMultiplier)
  {
    setAbility(other.ability);
  }

  float getAttackMultiplier() const
  {
    return attackMultiplier;
  }

  Mage &operator=(const Mage &other)
  {
    if (&other == this)
      return *this;
    Mage copy(other);
    swap(copy);
    return *this;
  }

  Player *clone() const override
  {
    return new Mage(*this);
  }

  void setAbility(const char *ability)
  {
    if (!ability)
    {
      throw std::invalid_argument("Ability cannot be null.");
    }

    delete[] this->ability;
    size_t len = strlen(ability);
    this->ability = new char[len + 1];
    strcpy(this->ability, ability);
  }
};

class PlayerCollection
{
  Player **player = nullptr;
  int size = 0;
  int cap = 0;

public:
  PlayerCollection() = default;

  PlayerCollection(const PlayerCollection &other)
      : size(other.size), cap(other.cap)
  {
    player = new Player *[cap];
    for (int c = 0; c < size; c++)
    {
      try
      {
        player[c] = other.player[c]->clone();
      }
      catch (const std::exception &ex)
      {
        for (int r = 0; r < c; r++)
        {
          player[r]->freeMem();
        }
        delete[] player;
        throw;
      }
    }
  }
  PlayerCollection &operator=(const PlayerCollection &) = delete;

  ~PlayerCollection()
  {
    for (int c = 0; c < size; c++)
    {
      player[c]->freeMem();
    }
    delete[] player;
  }

  void addPlayer(const Player &other)
  {
    if (size >= cap)
    {
      const int newCap = cap == 0 ? 8 : cap * 1.66;
      Player **newArr = new Player *[newCap];
      cap = newCap;
      for (int c = 0; c < size; c++)
      {
        newArr[c] = player[c];
      }

      delete[] player;
      player = newArr;
    }

    player[size++] = other.clone();
  }

  const Player &operator[](int index)
  {
    return *player[index];
  }

  const Player &operator[](int index) const
  {
    return *player[index];
  }

  int getSize() const
  {
    return size;
  }

  void removePlayer(const char *name)
  {
    for (int c = 0; c < size; c++)
    {
      if (strcmp(name, player[c]->getName()) == 0)
      {
        player[c]->freeMem();
        for (int r = c + 1; r < size; r++, c++)
        {
          player[c] = player[r];
        }
        --size;
      }
    }
  }
};

class Necromancer : public Mage
{
  PlayerCollection deadCopies;

public:
  Necromancer(const char *name, unsigned health, const Position &pos, Weapon weapon, unsigned damage, const char *ability, float multiplier)
      : Mage(name, health, pos, weapon, damage, ability, multiplier)
  {
  }

  void addPlayer(const Player &deadPlayer)
  {
    deadCopies.addPlayer(deadPlayer);
  }

  Player *clone() const override
  {
    return new Necromancer(*this);
  }

  Player *getRandomDeadPlayer() const
  {
    return const_cast<Player *>(
        deadCopies.getSize() == 0
            ? nullptr
            : &deadCopies[rand() % deadCopies.getSize()]);
  }
};

void Warrior::handleAttack(Player &other)
{
  if (abs(position - other.getPosition()) != Position{1, 1})
  {
    return;
  }

  if (other.getType() == PlayerType::Mage)
  {
    health *= static_cast<const Mage &>(other).getAttackMultiplier();
  }

  unsigned attackPower = other.getAttackPower();
  if (attackPower >= armor)
  {
    attackPower -= armor;
    armor = 0;
  }
  else
  {
    armor -= attackPower;
    return;
  }
  const bool isNecromancer = other.getType() == PlayerType::Necromancer;
  Necromancer *necro = isNecromancer ? static_cast<Necromancer *>(&other) : nullptr;

  if (attackPower >= health)
  {
    health = 0;
    if (necro)
    {
      necro->addPlayer(*this);
    }
    return;
  }
  else
  {
    health -= attackPower;
  }

  Player *otherAttacker = necro->getRandomDeadPlayer();
  if (otherAttacker)
  {
    handleAttack(*otherAttacker);
  }
}

void Player::handleAttack(Player &other)
{
  if (abs(position - other.position) != Position{1, 1})
  {
    return;
  }

  if (other.type == PlayerType::Mage)
  {
    health *= static_cast<const Mage &>(other).getAttackMultiplier();
  }

  if (other.attack_damage >= health)
  {
    health = 0;
  }
  else
  {
    health -= other.attack_damage;
  }

  const bool isNecromancer = other.getType() == PlayerType::Necromancer;
  Necromancer *necro = isNecromancer ? static_cast<Necromancer *>(&other) : nullptr;

  if (other.getAttackPower() >= health)
  {
    health = 0;
    if (necro)
    {
      necro->addPlayer(*this);
    }
    return;
  }
  else
  {
    health -= other.getAttackPower();
  }

  Player *otherAttacker = necro->getRandomDeadPlayer();
  if (otherAttacker)
  {
    if (type == PlayerType::Warrior)
    {
      static_cast<Warrior *>(this)->handleAttack(*otherAttacker);
    }
    else
    {
      handleAttack(*otherAttacker);
    }
  }
}

void Player::freeMem()
{
  switch (type)
  {
  case PlayerType::Player:
    delete static_cast<Player *>(this);
    break;
  case PlayerType::Necromancer:
    delete static_cast<Necromancer *>(this);
    break;
  case PlayerType::Mage:
    delete static_cast<Mage *>(this);
    break;
  case PlayerType::Warrior:
    delete static_cast<Warrior *>(this);
    break;
  }
}

int main()
{

  return 0;
}