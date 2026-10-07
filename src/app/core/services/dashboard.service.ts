import { Injectable } from '@angular/core';
import { Observable, of } from 'rxjs';
import { DashboardData } from '../models/dashboard.model';

@Injectable({
  providedIn: 'root',
})
export class DashboardService {
  getDashboardData(): Observable<DashboardData> {
    return of({
      userName: 'Jordan Miles',
      greeting: 'Good morning',
      initials: 'JM',
      balance: 12840.57,
      accountNumber: '4829',
      trend: 2.4,
      actions: [
        {
          label: 'Send',
          icon: 'north_east',
          route: '/send',
        },
        {
          label: 'Request',
          icon: 'south_west',
          route: '/request',
        },
        {
          label: 'Cards',
          icon: 'credit_card',
          route: '/cards',
        },
        {
          label: 'More',
          icon: 'more_horiz',
          route: '/more',
        },
      ],
      transactions: [
        {
          id: 1,
          title: 'Spotify',
          category: 'Subscription',
          amount: -9.99,
          icon: 'music_note',
        },
        {
          id: 2,
          title: 'Acme Corp',
          category: 'Salary',
          amount: 3200,
          icon: 'business_center',
        },
      ],
    });
  }
}
