import { db } from "./firebase-config.js";
import { ref, onValue } from "https://www.gstatic.com/firebasejs/9.23.0/firebase-database.js";

export function listenToSensors() {
  const sensorRef = ref(db, "iot");

  onValue(sensorRef, (snapshot) => {
  const d = snapshot.val() || {};

  updateSoil(d.soil);
  updateLight(d.ldr);
  updateMotion(d.pir);
});
}

function updateSoil(value) {
  document.getElementById("soilMoisture").innerText =
    value !== undefined ? value + " %" : "--";

  const status =
    value < 30 ? "Kering" :
    value < 70 ? "Cukup" :
    "Basah";

  document.getElementById("soilStatus").innerText = status;
}

function updateLight(value) {
  document.getElementById("lightLevel").innerText =
    value !== undefined ? value + " %" : "--";

  const status =
    value < 30 ? "Redup" :
    value < 70 ? "Cukup" :
    "Terang";

  document.getElementById("lightStatus").innerText = status;
}

function updateMotion(value) {
  document.getElementById("motion").innerText =
    value === 1 ? "Terdeteksi" : "Tidak Terdeteksi";

  const status =
    value === 1 ? "Ada Gerakan" : "Aman";

  document.getElementById("motionStatus").innerText = status;
}
