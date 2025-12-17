import { listenToSensors } from "./sensor.js";
import { auth } from "./firebase-config.js";
import {
  signInWithEmailAndPassword,
  signOut
} from "https://www.gstatic.com/firebasejs/9.23.0/firebase-auth.js";

const loginForm = document.getElementById("loginForm");
const dashboard = document.getElementById("dashboard");

document.getElementById("loginBtn").addEventListener("click", () => {
  const email = document.getElementById("email").value;
  const password = document.getElementById("password").value;

  signInWithEmailAndPassword(auth, email, password)
    .then(() => {
  loginForm.style.display = "none";
  dashboard.style.display = "block";
  listenToSensors();
})
    .catch(err => {
      alert("Login gagal: " + err.message);
    });
});

document.getElementById("logoutBtn").addEventListener("click", () => {
  signOut(auth).then(() => {
    dashboard.style.display = "none";
    loginForm.style.display = "block";
  });
});
