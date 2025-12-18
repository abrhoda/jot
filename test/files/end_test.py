from dataclasses import dataclass

@dataclass
class Weapon:
    kind: str
    value: int
    damage: int
    weight: int = 1
    bonus: float = 1.0

    def attack(self) -> float:
        print("I'm swinging my sword!")
        return self.damage*self.bonus

@dataclass
class Armor:
    kind: str
    value: int
    defense: int
    weight: int = 10
    bonus: float = 1.0

if __name__ == '__main__':
    sword = Weapon('sword', 10, 5, 1, 2.0)
    armor = Armor("pants", 100, 5)
    print('Hello, world! I have a strong sword but you have armor now!')
    sword.attack()
