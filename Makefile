# Makefile simplifié pour déploiement
# La compilation se fait maintenant avec CMake via ./cleanbuild

# IP du Luckfox
LUCKFOX_IP ?= 192.168.0.170

.PHONY: help deploy deploy-thermostat deploy-tests clean

help:
	@echo "Makefile Luckfox Panel 86"
	@echo ""
	@echo "IMPORTANT: Utiliser ./cleanbuild pour compiler"
	@echo ""
	@echo "Targets déploiement:"
	@echo "  deploy           - Déployer tous les binaires"
	@echo "  deploy-thermostat - Déployer seulement thermostat_demo"
	@echo "  deploy-tests     - Déployer seulement les tests"
	@echo ""
	@echo "Variables:"
	@echo "  LUCKFOX_IP       - IP du Luckfox (défaut: $(LUCKFOX_IP))"
	@echo ""
	@echo "Exemples:"
	@echo "  ./cleanbuild                    # Compiler"
	@echo "  make deploy                     # Déployer tout"
	@echo "  make deploy LUCKFOX_IP=192.168.1.100"

# Vérifier que les binaires existent
check-build:
	@if [ ! -d "build" ]; then \
		echo "ERREUR: Dossier build/ inexistant. Lancer ./cleanbuild d'abord."; \
		exit 1; \
	fi
	@if [ ! -f "build/thermostat_demo" ]; then \
		echo "ERREUR: build/thermostat_demo inexistant. Lancer ./cleanbuild d'abord."; \
		exit 1; \
	fi

# Déployer tout
deploy: check-build
	@echo "=== Déploiement sur Luckfox $(LUCKFOX_IP) ==="
	scp build/* root@$(LUCKFOX_IP):/tmp/
	@echo "✓ Tous les binaires déployés dans /tmp/"
	@echo ""
	@echo "Sur le Luckfox, exécuter:"
	@echo "  chmod +x /tmp/*"
	@echo "  /tmp/test_relays"
	@echo "  /tmp/test_rs485 -t messages"
	@echo "  /tmp/test_modbus -t write"
	@echo "  /tmp/test_temp_sensor"
	@echo "  /tmp/thermostat_demo"

# Déployer seulement thermostat
deploy-thermostat: check-build
	@echo "=== Déploiement thermostat sur $(LUCKFOX_IP) ==="
	scp build/thermostat_demo root@$(LUCKFOX_IP):/tmp/
	@echo "✓ thermostat_demo déployé"

# Déployer seulement tests
deploy-tests: check-build
	@echo "=== Déploiement tests sur $(LUCKFOX_IP) ==="
	scp build/test_* root@$(LUCKFOX_IP):/tmp/
	@echo "✓ Tests déployés"

# Nettoyer (CMake se charge du build)
clean:
	@echo "=== Nettoyage ==="
	rm -rf build
	@echo "✓ build/ supprimé"
	@echo "Pour recompiler: ./cleanbuild"