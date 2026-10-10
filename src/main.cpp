const loginScreen = document.getElementById('login-screen');
const dashboardScreen = document.getElementById('dashboard-screen');
const loginForm = document.getElementById('login-form');
const loginMessage = document.getElementById('login-message');
const logoutBtn = document.getElementById('logout-btn');

const occupancyRate = document.getElementById('occupancy-rate');
const availableRooms = document.getElementById('available-rooms');
const totalRevenue = document.getElementById('total-revenue');
const checkinsToday = document.getElementById('checkins-today');
const roomsList = document.getElementById('rooms-list');
const bookingsList = document.getElementById('bookings-list');

async function fetchJSON(url, options = {}) {
  const response = await fetch(url, {
    headers: { 'Content-Type': 'application/json' },
    ...options,
  });

  const data = await response.json();
  if (!response.ok) {
    throw new Error(data.message || 'Request failed');
  }

  return data;
}

function setScreen(isLoggedIn) {
  loginScreen.classList.toggle('active', !isLoggedIn);
  dashboardScreen.classList.toggle('active', isLoggedIn);
}

function updateDashboard(data) {
  occupancyRate.textContent = `${data.occupancyRate}%`;
  availableRooms.textContent = data.availableRooms;
  totalRevenue.textContent = `$${data.totalRevenue}`;
  checkinsToday.textContent = data.checkinsToday;

  roomsList.innerHTML = data.rooms
    .map(
      (room) => `
        <div class="room-item">
          <div class="room-meta">
            <strong>Room ${room.number}</strong>
            <span>${room.type}</span>
          </div>
          <span class="badge ${room.status.toLowerCase()}">${room.status}</span>
        </div>
      `
    )
    .join('');

  bookingsList.innerHTML = data.bookings
    .map(
      (booking) => `
        <div class="booking-item">
          <div class="booking-meta">
            <strong>${booking.guest}</strong>
            <span>Room ${booking.room}</span>
          </div>
          <span class="badge ${booking.status.toLowerCase()}">${booking.status}</span>
        </div>
      `
    )
    .join('');
}

async function loadDashboard() {
  try {
    const data = await fetchJSON('/api/dashboard');
    updateDashboard(data);
  } catch (error) {
    console.error(error);
  }
}

loginForm.addEventListener('submit', async (event) => {
  event.preventDefault();
  const username = document.getElementById('username').value.trim();
  const password = document.getElementById('password').value.trim();

  try {
    const result = await fetchJSON('/api/login', {
      method: 'POST',
      body: JSON.stringify({ username, password }),
    });

    if (result.success) {
      loginMessage.textContent = '';
      setScreen(true);
      loadDashboard();
    }
  } catch (error) {
    loginMessage.textContent = error.message;
  }
});

logoutBtn.addEventListener('click', () => {
  setScreen(false);
  loginForm.reset();
  loginMessage.textContent = '';
});

setScreen(false);
