from dataclasses import dataclass

@dataclass
class Weapon:
    kind: str
    value: int
    damage: int
    weight: int = 1
    bonus: float = 1.0

    def attack(self) -> float:
        return self.damage*self.bonus


if __name__ == '__main__':
    sword = Weapon('sword', 10, 5)
    print('Hello, world! I have a basic sword. Fear me!')
    sword.attack()
