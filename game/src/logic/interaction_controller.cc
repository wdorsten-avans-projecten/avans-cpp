#include "logic/interaction_controller.h"

namespace game::logic {

InteractionController::InteractionController() = default;
InteractionController::~InteractionController() = default;

void InteractionController::SetLogger(const std::shared_ptr<util::Logger> &logger) { logger_ = logger; }

void InteractionController::HandleVillageInteraction(domain::models::Player *p,
                                                     int turn_counter,
                                                     domain::models::Tile *t) {
  auto v = reinterpret_cast<domain::models::Village *>(t->GetTileContents());

  std::string input;

  while (!util::Validation::StringIsNumber(input)) {
    v->Interact();
    std::getline(std::cin, input);
  }

  switch (std::stoi(input)) {
    case 1:input = "";
      while (!util::Validation::StringIsNumber(input)) {
        std::cout << "Het dorp heeft " + std::to_string(v->GetTroopCount()) + " "
            + std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(v->GetTroopId())) + " te bieden."
                  << std::endl;
        std::cout << "Hoeveel manschappen wil je rekruteren?" << std::endl;
        std::getline(std::cin, input);
      }
      v->BuyTroops(p, std::stoi(input));
      logger_->WriteLine(
          "Beurt " + std::to_string(turn_counter) + ": Speler heeft " + input + " troepen met ID "
              + std::to_string(v->GetTroopId()) + " gekocht.");
      break;
    case 2:input = "";
      while (!util::Validation::StringIsNumber(input)) {
        std::cout << "Het dorp heeft " + std::to_string(v->GetProvisions()) + " proviand te bieden.";
        std::cout << "Hoeveel proviand wil je inslaan?" << std::endl;
        std::getline(std::cin, input);
      }

      v->BuyProvisions(p, std::stoi(input));
      logger_->WriteLine(
          "Beurt " + std::to_string(turn_counter) + ": Speler heeft " + input + " proviand ingeslagen.");
      break;
  }
}

void InteractionController::HandleCityInteraction(domain::models::Player *p,
                                                  int turn_counter,
                                                  domain::models::Tile *t) {
  auto c = reinterpret_cast<domain::models::City *>(t->GetTileContents());

  std::string input;

  while (!util::Validation::StringIsNumber(input)) {
    c->Interact();
    std::getline(std::cin, input);
  }

  switch (std::stoi(input)) {
    case 1:input = "";

      while (!util::Validation::StringIsNumber(input)) {
        std::cout << "De stad heeft " + std::to_string(c->GetTroopCount()) + " "
            + std::get<3>(db::DbWrapper::GetInstance()->GetTroopDataById(c->GetTroopId())) + " te bieden." << std::endl;
        std::cout << "Hoeveel manschappen wil je rekruteren?" << std::endl;
        input = "";

        std::getline(std::cin, input);
      }

      c->BuyTroops(p, std::stoi(input));
      logger_->WriteLine(
          "Beurt " + std::to_string(turn_counter) + ": Speler heeft " + input + " troepen met ID "
              + std::to_string(c->GetTroopId()) + " gekocht.");
      break;
    case 2:input = "";

      while (!util::Validation::StringIsNumber(input)) {
        std::cout << "Hoeveel proviand wil je inslaan?" << std::endl;
        std::getline(std::cin, input);
      }

      c->BuyProvisions(p, std::stoi(input));
      logger_->WriteLine(
          "Beurt " + std::to_string(turn_counter) + ": Speler heeft " + input + " proviand ingeslagen.");
      break;
    case 3:break;
  }
}

int InteractionController::HandleEnemyInteraction(domain::models::Enemy *e) {
  std::string input;

  while (!util::Validation::StringIsNumber(input)) {
    e->Interact();
    std::getline(std::cin, input);
  }

  return std::stoi(input);
}

bool InteractionController::HandleKingInteraction(domain::models::King *k, domain::models::Land *l) {
  auto kt = l->GetCurrentProvince()->GetTileByLocation(k->GetLocation());
  kt->SetTileContents(nullptr);
  kt->SetType(domain::enums::EMPTY);
  l->KillKing();
  return false;
}
} // namespace game::logic
