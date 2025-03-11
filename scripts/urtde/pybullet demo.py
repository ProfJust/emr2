import pybullet as p
import pybullet_data
import time

# Starten der PyBullet-Simulation
physics_client = p.connect(p.GUI)  # GUI-Modus für Visualisierung
p.setAdditionalSearchPath(pybullet_data.getDataPath())  # Standard-URDF-Dateien laden

# Laden des Roboterarms (z. B. KUKA oder UR5)
#robot_id = p.loadURDF("kuka_iiwa/model.urdf", useFixedBase=True)
robot_id = p.loadURDF("/home/oju/pybullet_ur5_robotiq/urdf/ur5_robotiq_85.urdf", useFixedBase=True)

# Schwerkraft und Boden hinzufügen
p.setGravity(0, 0, -9.8)
plane_id = p.loadURDF("plane.urdf")

# Simulationseinstellungen
p.setRealTimeSimulation(0)  # Echtzeitsimulation deaktivieren
time_step =  1./8. #      240.
p.setTimeStep(time_step)

# Gelenksteuerung: Zielpositionen festlegen
target_positions = [0.5, 0.3, -0.2, 0.5, -0.3, 0.2, 0]  # Gelenkwinkel in Radiant

# Hauptschleife der Simulation
for step in range(1000):
    for joint_index in range(p.getNumJoints(robot_id)):
        p.setJointMotorControl2(
            bodyUniqueId=robot_id,
            jointIndex=joint_index,
            controlMode=p.POSITION_CONTROL,
            targetPosition=target_positions[joint_index % len(target_positions)],
            force=500  # Maximale Kraft für die Bewegung
        )
    p.stepSimulation()
    time.sleep(time_step)

# Simulation beenden
p.disconnect()
