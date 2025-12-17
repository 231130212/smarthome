// Import Firebase
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.23.0/firebase-app.js";
import { getAuth } from "https://www.gstatic.com/firebasejs/9.23.0/firebase-auth.js";
import { getDatabase } from "https://www.gstatic.com/firebasejs/9.23.0/firebase-database.js";

// Konfigurasi Firebase
const firebaseConfig = {
  apiKey: "AIzaSyBWykaVcM4DaQ-XBfF6CLQXoX2bfi96Cto",
  authDomain: "minggu11-d956b.firebaseapp.com",
  databaseURL: "https://minggu11-d956b-default-rtdb.firebaseio.com",
  projectId: "minggu11-d956b",
  storageBucket: "minggu11-d956b.firebasestorage.app",
  messagingSenderId: "920306875576",
  appId: "1:920306875576:web:be1bd99efda2a8aedc884d"
};

// Init Firebase
const app = initializeApp(firebaseConfig);
export const auth = getAuth(app);
export const db = getDatabase(app);
